import os, sys
import os.path
from pydub import AudioSegment
import mimi
from timer import timer


class Mp3Generator(object):
    def generate(self, wav_path, output_path):
        if not os.path.exists(wav_path):
            raise Exception('file: {} not exist'.format(wav_path))

        dir_name = os.path.dirname(output_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)

        song = AudioSegment.from_wav(wav_path)
        song.export(output_path, format='mp3')


class WavGenerator(object):
    def generate(self, midi_file_path, output_path):
        if not os.path.exists(midi_file_path):
            raise Exception('file: {} not exist'.format(midi_file_path))

        dir_name = os.path.dirname(output_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)

        mimi.output.midi2wav(midi_file_path, output_path)


class MidiGenerator(object):
    def generate(self, midi_txt_file_path, output_path):
        if not os.path.exists(midi_txt_file_path):
            raise Exception('file: {} not exist'.format(midi_txt_file_path))

        dir_name = os.path.dirname(output_path)
        if not os.path.exists(dir_name):
            os.makedirs(dir_name)

        cmd = 't2mf {} {}'.format(midi_txt_file_path, output_path)
        os.system(cmd)


if __name__ == '__main__':
    base_dir = '/root/data/'
    g = MidiGenerator()
    g.generate(base_dir + 'test.txt', base_dir + 'test.mid')
    g = WavGenerator()
    g.generate(base_dir + 'test.mid', base_dir + 'test.wav')
    g = Mp3Generator()
    g.generate(base_dir + 'test.wav', base_dir + 'test.mp3')
    print('Done!')
