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
Convert the obtained pose information to the numpy npz form
Need to follow the order of conversion, information file format [video name].[Serial number].keypoints.json
e.g: Video0.mp4.0001_keypoints.json
Among them, this serial number is 4 digits and it starts to grow according to 0000
Location of pose information in json:people.[pose_keypoints_2d]
There may be more than one person and the approach is to take only the first person's information
If no pose information is detected, the previous pose information is used as this information.
"""

import os, sys
import json
import numpy as np
import datetime
from midi import DriveMidiConversion

POSE_ROOT = '/root/data/google_driver/json/'
starttime = datetime.datetime.now()
if not os.path.exists(POSE_ROOT):
    raise Exception('path:' + POSE_ROOT + " not exist")


def get_pose_info(path):
    # print("handle: "+path)
    if not os.path.exists(path):
        raise Exception("file: " + path + " not exist")
    f = open(path, 'r')
    content = f.read()
    f.close()
    data = json.loads(content)
    # print('data: '+str(data))
    people = data['people']
    if people is None:
        raise Exception("data:" + data + " has not people info")
    if len(people) == 0:
        print("people has not pose info", path)
        return None
    else:
        return people[0]["pose_keypoints_2d"]


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


pose_infos = []
for dir1 in os.listdir(POSE_ROOT):
    # If not a directory, ignore
    if os.path.isfile(POSE_ROOT + '/' + dir1):
        print("ignore file:" + dir1)
        continue
    # video type level
    type_level_infos = []
    for dir2 in os.listdir(POSE_ROOT + '/' + dir1):
        # e.g: Video0.mp4.0001_keypoints.json
        dir = POSE_ROOT + '/' + dir1 + '/' + dir2
        # ignore file
        if os.path.isfile(dir):
            print("ignore file:" + dir2)
            continue
        # construct number
        n_files = len(os.listdir(dir))
        # The pose information in each folder is stored in a separate array
        # video level
        infos = []
        last_info = None
        for index in range(n_files):
            # construct filename
            filename = dir2 + '.' + str(index + 1).zfill(4) + "_keypoints.json"
            path = dir + '/' + filename
            info = get_pose_info(path)
            if info is None:
                if last_info is None:
                    # raise Exception("Pose Info Error")
                    info = [0 for x in range(54)]
                info = last_info
            last_info = info
            # Save pose info
            infos.append(info)
        # Add label information here
        num = get_type_num(dir1)
        if num is None:
            raise Exception('Unsuport type ', dir1)
        labels = DriveMidiConversion.extract(num, len(infos))
        type_level_infos.append((infos, labels))
    pose_infos.append(type_level_infos)
# Finally, convert to npz
data = np.array(pose_infos)
np.savez('pose.npz', data)
endtime = datetime.datetime.now()
print('times: ', (endtime - starttime).seconds, ' seconds')
