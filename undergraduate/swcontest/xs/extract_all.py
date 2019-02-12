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
All video is extracted at 12 frames per second
All data is placed under DATASET_ROOT and each category is placed in a folder
The extracted frames are placed under OUTPUT_ROOT/frames. Each class is in a folder.
Each video frame is extracted under the video command folder.
"""
import os, sys
import datetime

DATASET_ROOT = '/root/data/google_driver/video/'
OUTPUT_ROOT = '/root/data/google_driver/'


# Get extract frame commands
def get_cmd(file, frames=12):
    # 获取最短的文件名
    basename = os.path.basename(file)
    output_path = OUTPUT_ROOT + 'frames/' + file
    input_path = DATASET_ROOT + file
    if not os.path.exists(output_path):
        os.makedirs(output_path)
    cmd = 'ffmpeg -i ' + input_path + ' -r ' + str(frames) + ' ' + output_path + '/' + basename + '.%4d.jpg > /dev/null'
    return cmd


starttime = datetime.datetime.now()
# Traverse DATASET_ROOT
dirs = os.listdir(DATASET_ROOT)
for dir in dirs:
    for file in os.listdir(DATASET_ROOT + '/' + dir):
        # If it is not a .mp4 and .mpg suffix, ignore
        if not (file.endswith('mp4') or file.endswith('mpg')):
            print('ignore ', file)
        else:
            # extract frame
            cmd = get_cmd(dir + '/' + file)
            print(cmd)
            os.system(cmd)

endtime = datetime.datetime.now()
print((endtime - starttime).seconds)
