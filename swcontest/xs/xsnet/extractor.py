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
Extract data in an object-oriented manner
"""
import os, sys

sys.path.append('..')
import os.path
import json
import numpy as np
import midi.DriveMidiConversion
from timer import timer

def get_type_num(dir):
    data = {
        'BboomBboom': 0,
        'Confession_Balloon': 2,
        'seve': 5,
        'goodtime': 6,
        'jilejingtu': 5,
        'panama': 1,
        'shapeofyou': 3
    }
    return data[dir]


def get_label(type_name, n_len):
    num = get_type_num(type_name)
    labels = midi.DriveMidiConversion.extract(num, n_len)
    return np.array(labels).astype(np.int32)


class FramesExtractor(object):
    """
    Use ffmpeg to extract frames
    """
    def extract(self, video_path, output_path, frames=12, with_output=False, show_cmd=True):
        if not os.path.exists(video_path):
            raise Exception('video file not exist')
        basename = os.path.basename(video_path)
        if not os.path.exists(output_path):
            os.makedirs(output_path)
        cmd = 'ffmpeg -i {} -r {} {}/{}.%4d.jpg'.format(video_path, frames, output_path, basename)
        if not with_output:
            cmd = '{} > /dev/null'.format(cmd)

        if show_cmd:
            print(cmd)
        os.system(cmd)

    def extract_folder(self, folder_path, output_path):
        if not os.path.exists(folder_path):
            raise Exception('folder not exist')
        for it in os.listdir(folder_path):
            video_path = os.path.join(folder_path, it)
            frames_output_path = os.path.join(output_path, it)
            self.extract(video_path, frames_output_path)


class PoseExtractor(object):
    """
    Use openpose to extract pose info
    """

    def __init__(self, openpose_root_path):
        self.openpose_root_path = openpose_root_path
        self.openpose_bin_path = os.path.join(openpose_root_path, 'build/examples/openpose/openpose.bin')

    def extract(self, frames_path, output_path, with_output=False, show_cmd=True):
        os.chdir(self.openpose_root_path)
        cmd = '{} --image_dir {} --write_json {} --display 0 --keypoint_scale 3'.format(self.openpose_bin_path,
                                                                                        frames_path, output_path)
        if not with_output:
            cmd = '{} > /dev/null'.format(cmd)

        if show_cmd:
            print(cmd)

        os.system(cmd)

    def extract_foler(self, folder_path, output_path):
        if not os.path.exists(folder_path):
            raise Exception('folder not exist')
        for it in os.listdir(folder_path):
            frames_path = os.path.join(folder_path, it)
            json_output_path = os.path.join(output_path, it)
            self.extract(frames_path, json_output_path)


class DataExtractor(object):
    def _get_pose_info(self, json_file_path):
        if not os.path.exists(json_file_path):
            raise Exception("file: {} not exist".format(json_file_path))
        f = open(json_file_path, 'r')
        data = f.read().strip()
        if len(data) == 0:
            raise Exception('file content is empty')
        f.close()
        try:
            data = json.loads(data)
        except json.decoder.JSONDecodeError as e:
            print(e)
            return None
        people = data['people']
        if people is None:
            raise Exception('data: {} has not people info'.format(data))
        if len(people) == 0:
            # print('file: {} has not pose info'.format(json_file_path))
            return None
        else:
            return people[0]['pose_keypoints_2d']

    def extract_with_none(self, json_path):
        """
        对于没有节点信息的图片，去掉，同时考虑分成两个组，递归去做，直到所有的都不为空
        """
        if not os.path.exists(json_path):
            raise Exception('path not exist')

        data = []
        for it in os.listdir(json_path):
            file_path = os.path.join(json_path, it)
            ret = self._get_pose_info(file_path)
            # 这里会导致ValueError: The truth value of an array with more than one element is ambiguous. Use a.any() or a.all()
            if ret is None:
                data.append(ret)
            else:
                data.append(np.array(ret).astype(np.float32))

        return data

    def extract(self, json_path):

        if not os.path.exists(json_path):
            raise Exception('path not exist')
        last = None
        data = []
        for it in os.listdir(json_path):
            file_path = os.path.join(json_path, it)
            ret = self._get_pose_info(file_path)
            if ret is None:
                if last is None:
                    ret = [0 for i in range(54)]
                else:
                    ret = last
            assert len(ret) != 0
            last = ret
            data.append(np.array(ret).astype(np.float32))

        return np.array(data).astype(np.float32)

    def _extract_folder1_and_split_none(self, folder_path, with_label=True):
        if not os.path.exists(folder_path):
            raise Exception('folder: {} not exist'.format(folder_path))

        data = []
        labels = []
        for it in os.listdir(folder_path):
            file_path = os.path.join(folder_path, it)
            ret = self.extract_with_none(file_path)
            if with_label:
                type = os.path.basename(folder_path)
                label = get_label(type, len(ret))
            # 分割
            # 找到所有的下标
            ind = [i for i in range(len(ret)) if ret[i] is None]
            print(ind)
            ind.append(len(ret))
            last_pos = 0
            for it in ind:
                t_data = ret[last_pos:it]
                # 保证每个数据项不为空
                if len(t_data) != 0:
                    # 对数据进行分割，每个的大小控制在200个以内
                    t_ind = 0
                    while t_ind < len(t_data):
                        end_ind = min(t_ind + 200, len(t_data))
                        t_sub_data = t_data[t_ind:end_ind]
                        t_ind = t_ind + 200
                        data.append(np.array(t_sub_data))
                    # data.append(np.array(t_data))
                    if with_label:
                        t_label = label[last_pos:it]
                        t_ind = 0
                        while t_ind < len(t_label):
                            end_ind = min(t_ind + 200, len(t_label))
                            t_sub_label = t_label[t_ind:end_ind]
                            t_ind = t_ind + 200
                            labels.append(np.array(t_sub_label).astype(np.int32))
                last_pos = it + 1
        # 是否已经把最后一个算进去了？　在列表后面再加一个最后的下标
        # 如果最后一个本身是空，也不影响结果
        return data, labels

    def _extract_folder1(self, folder_path, with_label=True):
        if not os.path.exists(folder_path):
            raise Exception('folder: {} not exist'.format(folder_path))
        data = []
        labels = []
        for it in os.listdir(folder_path):
            file_path = os.path.join(folder_path, it)
            ret = self.extract(file_path)
            data.append(ret)
            if with_label:
                type = os.path.basename(folder_path)
                label = get_label(type, len(ret))
                labels.append(label)

        return data, labels

    def extract_folder1(self, folder_path, with_label=True, split_none=True):
        if split_none:
            ret = self._extract_folder1_and_split_none(folder_path, with_label)
        else:
            ret = self._extract_folder1(folder_path, with_label)
        if with_label:
            return np.array(ret[0]), np.array(ret[1])
        else:
            return np.array(ret[0]),

    def extract_folder2(self, folder_path, with_label=True, split_none=True):
        if not os.path.exists(folder_path):
            raise Exception('folder: {} not exist'.format(folder_path))
        data = []
        labels = []
        for it in os.listdir(folder_path):
            dir_path = os.path.join(folder_path, it)
            if split_none:
                ret = self._extract_folder1_and_split_none(dir_path, with_label=with_label)
            else:
                ret = self._extract_folder1(dir_path, with_label)
            data.extend(ret[0])
            if with_label:
                labels.extend(ret[1])

        if with_label:
            return np.array(data), np.array(labels)
        return np.array(data),

    def extract_folder(self, folder_path, folder_level=2):
        if not os.path.exists(folder_path):
            raise Exception('folder: {} not exist'.format(folder_path))
        if folder_level > 2:
            raise Exception('unsupport level > 2')


if __name__ == '__main__':
    ex = FramesExtractor()
    video_path = '/home/pikachu/Videos/形声.mp4'
    output_path = '/home/pikachu/Videos/frames/形声.mp4'
    # ex.extract(video_path, output_path)
    # ex = PoseExtractor()
    ex = DataExtractor()
    # ret = ex.extract('/home/pikachu/Documents/json/seve/Video1_clip.mp4')
    # ret = ex.extract_folder1('/home/pikachu/Documents/json/seve', split_none=True)
    # print('ret[0].shape:{} ret[1].shape:{}'.format(ret[0].shape, ret[1].shape))
    # ret = ex.extract_folder2('/home/pikachu/Documents/json', split_none=True)
    # ret = ex.extract_folder1('/root/data/google_driver/json/seve', split_none=True)
    ret = ex.extract_folder2('/root/data/google_driver/json', split_none=True)
    npz = 'data_with_label_split_none.npz'
    np.savez(npz, ret[0], ret[1])
    ret = np.load(npz)
    ret0 = ret['arr_0']
    ret1 = ret['arr_1']
    print('ret0.shape:{} ret1.shape:{}'.format(ret0.shape, ret1.shape))
    # print(ret.shape)
    # print(ret0.shape,ret1.shape)
    # for it in range(len(ret0)):
    #     print('{} <-> {}'.format(ret0[it]),ret1[it])
