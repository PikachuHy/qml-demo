import os, sys

sys.path.append('..')
import hashlib
from chainer import serializers
import chainer.backends
import cupy as cp
from extractor import FramesExtractor, PoseExtractor, DataExtractor
from generator import MidiGenerator, WavGenerator, Mp3Generator
from datasets import load_midi_snippet
from model import XSNet
from midi.DriveMidiConversion import make_midi
from timer import timer

cur_dir = os.path.split(os.path.realpath(__file__))[0]


class XSNetPredictor(object):
    def __init__(self, openpose_root, midi_database_path, model_path, device=0):
        self.openpose_root = openpose_root
        self.midi_database_path = midi_database_path
        self.model_path = model_path
        self.device = device

    def generate(self, midi_txt_path, ret, id, tmp_path, e_name, ouput_mp3_path):
        e_name = '{}_{}'.format(e_name,id)
        make_midi(midi_txt_path, ret[0], id)
        midi_path = os.path.join(tmp_path, e_name + '.mid')
        wav_path = os.path.join(tmp_path, e_name + '.wav')
        MidiGenerator().generate(midi_txt_path + '.txt', midi_path)
        WavGenerator().generate(midi_path, wav_path)
        dir_path = os.path.dirname(ouput_mp3_path)
        ouput_mp3_path = os.path.join(dir_path,e_name+'.mp3')
        Mp3Generator().generate(wav_path, ouput_mp3_path)
        return e_name+'.mp3'

    def predict(self, mp4_path, ouput_mp3_path, tmp_path=None):
        if not os.path.exists(mp4_path):
            raise Exception('file: {} not exist'.format(mp4_path))
        dir_name = os.path.dirname(ouput_mp3_path)
        basename = os.path.basename(ouput_mp3_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)

        h = hashlib.md5()
        h.update(basename.encode(encoding='utf-8'))
        e_name = h.hexdigest()

        if tmp_path is None:
            tmp_path = os.path.join(dir_name, e_name)
        else:
            tmp_path = os.path.join(tmp_path, e_name)
        if not os.path.exists(tmp_path):
            os.makedirs(tmp_path)

        frames_path = os.path.join(tmp_path, 'frames')
        pose_path = os.path.join(tmp_path, 'json')
        FramesExtractor().extract(mp4_path, frames_path)
        PoseExtractor(self.openpose_root).extract(frames_path, pose_path)
        data = DataExtractor().extract(pose_path)

        model = self._init_model()
        chainer.backends.cuda.get_device_from_id(0).use()
        model.to_gpu()  # Copy the model to the GPU
        ret = model.translate(cp.array(data))

        os.chdir(cur_dir)
        midi_txt_path = os.path.join(tmp_path, e_name)
        l = []
        # 钢琴　吉他　小提琴　贝司
        for id in [0, 24, 40, 32]:
            path = self.generate(midi_txt_path, ret, id, tmp_path, e_name, ouput_mp3_path)
            l.append(path)
        return l

    def _init_model(self):
        os.chdir(cur_dir)
        midi_ids = load_midi_snippet(self.midi_database_path)
        n_rhythm = len(midi_ids)
        model = XSNet(3, 54, n_rhythm, 1024)
        serializers.load_npz(self.model_path, model)
        return model


if __name__ == '__main__':
    openpose_root = '/root/data/openpose'
    midi_database_path = '../midi/database.txt'
    model_path = 'result/model_epoch-294'
    p = XSNetPredictor(openpose_root, midi_database_path, model_path)
    p.predict('/root/data/Video100.mp4', '/root/data/tmp/test100.mp3')
