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
Prepare neural network training data sets
For video, use openpose to extract body keypoints
For Audio, use midi file to construct data
"""
import numpy as np
from chainer.datasets import tuple_dataset

EOS = 0


def load_midi_snippet(path):
    """
    把所有的标签加１
    把零作为空
    """
    with open(path) as f:
        # midi_snippets = {line.strip(): i for i, line in enumerate(f)}
        midi_snippets = {line.strip(): i + 1 for i, line in enumerate(f)}
        midi_snippets['<EOS>'] = 0
    return midi_snippets


def get_tuple(data):
    data = np.array(data)
    print('get_tuple data:', data.shape)
    t_data = []
    t_label = []
    for it in data:
        if len(it[0]) == 0:
            it[0].append([0 for i in range(54)])
            it[1].append(0)
        t_data.append(np.array(it[0]).astype(np.float32))
        t_label.append(np.array(it[1]).astype(np.int32))
    t_data = np.array(t_data)
    t_label = np.array(t_label)
    print("t_data:", t_data.shape)
    print("t_data[0].shape:", t_data[0].shape)
    return tuple_dataset.TupleDataset(t_data, t_label)


def get_data():
    DATASET_PATH = 'pose.npz'
    train = []
    test = []
    data = np.load(DATASET_PATH)
    data = data['arr_0']
    data = np.array(data)
    print('type num:', len(data), data.shape)
    for it in data:
        it = np.array(it)
        print('video num:', len(it))
        # Use 90% for the training set and 10% for the test set
        n = len(it) * 0.9
        n = int(n)
        t_train = it[:n]
        t_test = it[n + 1:]
        train.extend(t_train)
        test.extend(t_test)

    train = np.array(train)
    test = np.array(test)
    print(len(train), len(test), train.shape, test.shape)
    print(len(train[0]))
    train = get_tuple(train)
    test = get_tuple(test)
    return train, test


def get_new_tuple(data_list):
    data = []
    label = []
    for it in data_list:
        if len(it[0]) == 0:
            continue
        assert len(it[0]) != 0
        assert len(it[0]) == len(it[1])
        for x in it[0]:
            assert len(x) == 54
        data.append(it[0])
        # 为了方便后续的计算，对每个标签进行加１
        label.append(it[1] + 1)

    data = np.array(data)
    label = np.array(label)
    return tuple_dataset.TupleDataset(data, label)


def get_new_data(path='data_with_label.npz'):
    # npz = 'data_with_label.npz'
    npz = path
    ret = np.load(npz)
    ret0 = ret['arr_0']
    ret1 = ret['arr_1']
    l_ret0 = ret0.tolist()
    l_ret1 = ret1.tolist()
    ret = zip(l_ret0, l_ret1)
    l_ret = list(ret)
    # random.shuffle(l_ret)
    # ================
    n_len = len(l_ret)
    # index = n_len * 0.618
    # index = index * 0.618
    # index = int(index)
    # l_ret = l_ret[:index]
    # l_ret = l_ret[:151]
    # =================
    n_len = len(l_ret)
    n = n_len * 0.9
    n = int(n)
    train = l_ret[:n]
    test = l_ret[n + 1:]
    train = get_new_tuple(train)
    test = get_new_tuple(test)
    return train, test


if __name__ == '__main__':
    # get_data()
    get_new_data()
