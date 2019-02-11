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
Build a server and export interface to user
"""
import os
import sys
sys.path.append('..')
from flask import Flask, render_template, request, flash, redirect, url_for, jsonify
from werkzeug.utils import secure_filename
import datetime
import hashlib
from predictor import XSNetPredictor
app = Flask(__name__)

UPLOAD_FOLDER = '/root/data/video/'
ALLOWED_EXTENSIONS = set(['mp4'])
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

app.config['SECRET_KEY'] = os.urandom(24)
cur_dir = os.path.split(os.path.realpath(__file__))[0]


def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


def generate_music(path):
    """
    生成音乐，大致流程为
    将视频变成图片帧 12帧每秒
    使用openpose提取节点信息
    规整输入
    使用xsnet进行预测
    根据预测得到的标签，生成txt文本
    将txt文本转换为mid文件
    将mid文件转换为wav文件
    将wav文件转换为mp3文件
    返回mp3文件的URL地址，相对服务器的
    :param path:
    :return:
    """
    # If it is not a video, throw an exception file type error
    if not os.path.exists(path):
        raise Exception('file: {}  not exist'.format(path))
    if not path.endswith('.mp4'):
        raise Exception('file is invalid')
    # Get filename
    print('Encrypted file name...')
    filename = os.path.basename(path)
    h1 = hashlib.md5()
    h1.update(filename.encode(encoding='utf-8'))
    e_filename = h1.hexdigest()
    print('cur name:{}'.format(e_filename))
    openpose_root = '/root/data/openpose'
    midi_database_path = '../midi/database.txt'
    model_path = 'result/model_epoch-294'
    p = XSNetPredictor(openpose_root, midi_database_path, model_path)
    l = p.predict(path,'/root/data/xs/xsnet/static/{}.mp3'.format(e_filename),'/root/data/flask/xsnet')
    l_path = ['http://47.95.203.153/static/{}'.format(it) for it in l]
    return l_path


@app.route('/upload_file', methods=['GET'])
def upload_index():
    return """
        <!doctype html>
        <title>Upload new File</title>
        <h1>Upload new File</h1>
        <form method=post enctype=multipart/form-data action=/upload_file>
          <input type=file name=file>
          <input type=submit value=Upload>
        </form>
        """


@app.route('/upload_file', methods=['POST'])
def upload_file():
    """
    Accept the video file uploaded by the client and return the score result
    :return:
    """
    ret = {'code': 200, 'status': True, 'data': [], 'msg': 'ok'}
    if 'file' not in request.files:
        flash('No file part')
        ret['status'] = False
        ret['code'] = 400
        ret['msg'] = 'No file part'
        return jsonify(ret)
    file = request.files['file']
    if file.filename == '':
        flash('No selected file')
        ret['status'] = False
        ret['code'] = 400
        ret['msg'] = 'No file part'
        return jsonify(ret)
    if file and allowed_file(file.filename):
        begin = datetime.datetime.now()
        filename = secure_filename(file.filename)
        path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(path)
        urls = generate_music(path)
        # url = 'http://47.95.203.153/static/my_test.mp3'
        print('url: {}'.format(urls))
        # ret['data'] = [url, url, url]
        ret['data'] = urls
        end = datetime.datetime.now()
        print('total cost time: {}'.format(end-begin))
        return jsonify(ret)
    else:
        ret['status'] = False
        ret['code'] = 400
        ret['msg'] = 'File not valid. Please upload .mp4 file.'
        return jsonify(ret)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
    # path = '/root/data/video/v1.mp4'
    # generate_music(path)
