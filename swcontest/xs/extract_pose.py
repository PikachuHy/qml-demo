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
All data is placed under DATASET_ROOT and each category is placed in a folder
Extracted frames are placed under OUTPUT_ROOT/pose, each category is in a folder,
and each video extracted frame is under the video-named folder
"""
import os, sys
import datetime

DATASET_ROOT = '/root/data/google_driver/frames/'
OUTPUT_ROOT = '/root/data/google_driver/'
OPENPOSE_ROOT = '/root/data/openpose/'


# Get extract pose commands
def get_cmd(dir):
    #  ./build/examples/openpose/openpose.bin --image_dir /home/pikachu/Desktop/test --write_json /home/pikachu/Desktop/test --net_resolution 192x144 --display 0
    bin_path = OPENPOSE_ROOT + '/build/examples/openpose/openpose.bin'
    image_dir = DATASET_ROOT + dir
    write_json_path = OUTPUT_ROOT + 'json/' + dir
    if not os.path.exists(write_json_path):
        os.makedirs(write_json_path)
    cmd = bin_path + ' --image_dir ' + image_dir + ' --write_json ' + write_json_path + ' --display 0 --keypoint_scale 3 > /dev/null'
    return cmd


starttime = datetime.datetime.now()
os.chdir(OPENPOSE_ROOT)
# Traverse DATASET_ROOT
# Actually, according to my directory structure, only two layers need to follow.
# One layer is big, one layer is concrete
dirs = os.listdir(DATASET_ROOT)
for dir1 in dirs:
    for dir2 in os.listdir(DATASET_ROOT + '/' + dir1):
        # The video frame directory
        dir = dir1 + '/' + dir2
        cmd = get_cmd(dir)
        print(cmd)
        os.system(cmd)

endtime = datetime.datetime.now()
print('times: ', (endtime - starttime).seconds, ' seconds')
