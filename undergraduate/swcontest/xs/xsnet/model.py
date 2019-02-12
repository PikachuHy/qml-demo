# -*- coding: UTF-8 -*-
# Copyright 2018 PikachuHy. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
"""
Define a neural network that converts the rhythm of motion into music
Based on information already available define a neural network similar to Seq2Seq
"""
import cupy as cp
import numpy as np
import chainer
from chainer.backends import cuda
from chainer import Function, gradient_check, report, training, utils, Variable
from chainer import datasets, iterators, optimizers, serializers
from chainer import Link, Chain, ChainList
import chainer.functions as F
import chainer.links as L
from chainer.training import extensions
import argparse
from chainer.functions.loss import softmax_cross_entropy
from chainer.functions.evaluation import accuracy
from chainer import reporter

EOS = 0


def sequence_embed(embed, xs):
    x_len = [len(x) for x in xs]
    x_section = np.cumsum(x_len[:-1])
    t = F.concat(xs, axis=0)
    if t.data.shape[0] == 0:
        print('t.data.shape:{}'.format(t.data.shape))
    ex = embed(t)
    exs = F.split_axis(ex, x_section, 0)
    return exs


class XSNet(Chain):
    def __init__(self, n_layers, n_source_pose_node, n_target_rhythm, n_units):
        super(XSNet, self).__init__()
        with self.init_scope():
            self.embed_x = L.Linear(n_source_pose_node, n_units)
            self.embed_y = L.EmbedID(n_target_rhythm, n_units)
            self.encoder = L.NStepLSTM(n_layers, n_units, n_units, 0.1)
            self.decoder = L.NStepLSTM(n_layers, n_units, n_units, 0.1)
            self.W = L.Linear(n_units, n_target_rhythm)

        self.n_layers = n_layers
        self.n_units = n_units

    def __call__(self, xs, ys):
        xs = [x[::-1] for x in xs]
        eos = self.xp.array([EOS], np.int32)
        ys_in = [F.concat([eos, y], axis=0) for y in ys]
        exs = sequence_embed(self.embed_x, xs)
        eys = sequence_embed(self.embed_y, ys_in)
        hx, cx, _ = self.encoder(None, None, exs)
        _, _, os = self.decoder(hx, cx, eys)
        concat_os = F.concat(os, axis=0)
        h = self.W(concat_os)
        return h

    def translate(self, xs, cur_max_index = 1):
        """
        每次保证只传一个视频
        :param xs:
        :param max_length:
        :return:
        """
        max_length = len(xs)
        xs = [xs]
        batch = len(xs)
        with chainer.no_backprop_mode(), chainer.using_config('train', False):
            xs = [x[::-1] for x in xs]
            exs = sequence_embed(self.embed_x, xs)
            h, c, _ = self.encoder(None, None, exs)
            ys = self.xp.full(batch, EOS, np.int32)
            result = []
            for i in range(max_length):
                eys = self.embed_y(ys)
                eys = F.split_axis(eys, batch, 0)
                h, c, ys = self.decoder(h, c, eys)
                cys = F.concat(ys, axis=0)
                wy = self.W(cys)
                # 想办法生成３个
                tmp = []
                for i in range(cur_max_index):
                    ys = self.xp.argmax(wy.data, axis=1).astype(np.int32)
                    t = wy.data[0][ys]
                    tmp.append((ys,t))
                    wy.data[0][ys]=-1
                # 把它复原，看能不能那么乱
                for i in range(cur_max_index):
                    yss,t = tmp[i]
                    wy.data[0][yss] = t
                result.append(ys)

            # Using `xp.concatenate(...)` instead of `xp.stack(result)` here to
            # support np 1.9.
            result = cuda.to_cpu(
                self.xp.concatenate([self.xp.expand_dims(x, 0) for x in result]).T)
            return result


class Classifier(Chain):
    compute_accuracy = True

    def __init__(self, predictor,
                 accfun=accuracy.accuracy):
        super(Classifier, self).__init__()
        self.accfun = accfun
        self.y = None
        self.loss = None
        self.accuracy = None

        with self.init_scope():
            self.predictor = predictor

    def __call__(self, xs, ys):
        eos = self.xp.array([EOS], np.int32)
        ys_out = [F.concat([y, eos], axis=0) for y in ys]
        concat_ys_out = F.concat(ys_out, axis=0)
        batch = len(xs)
        self.y = self.predictor(xs, ys)
        self.loss = F.sum(F.softmax_cross_entropy(self.y, concat_ys_out, reduce='no')) / batch
        reporter.report({'loss': self.loss}, self)
        if self.compute_accuracy:
            self.accuracy = self.accfun(self.y, concat_ys_out)
            reporter.report({'accuracy': self.accuracy}, self)
        return self.loss
