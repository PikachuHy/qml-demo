from chainer import datasets, iterators, optimizers, serializers, config
import chainer.backends
from model import XSNet, Classifier
from train import handle_data, load_midi_snippet, convert
import datasets
from extractor import DataExtractor
import cupy as cp
from timer import timer


@timer
def my_test():
    ex = DataExtractor()
    ret = ex.extract('/home/pikachu/Documents/json/seve/Video1_clip.mp4')
    # ret = ex.extract('/root/data/google_driver/json/seve/Video149.mpg')
    target_midi_ids = load_midi_snippet('../midi/database.txt')
    target_midi_ids = {i: w for w, i in target_midi_ids.items()}
    n_rhythm = len(target_midi_ids)
    print('rhythm: {}'.format(n_rhythm))
    model = XSNet(3, 54, n_rhythm, 1024)
    chainer.backends.cuda.get_device_from_id(0).use()
    model.to_gpu()  # Copy the model to the GPU
    npz_path = 'result/model_epoch-80'
    serializers.load_npz(npz_path, model)

    ret = ret[0:min(len(ret), 200)]
    ret = model.translate(cp.array(ret))
    print(ret[0], len(ret[0]))


@timer
def my_test_2(a):
    print('t')
    print('发生了什么')

@timer
def my_test_3():
    print('t')
    print('发生了什么')

if __name__ == '__main__':
    # my_test()
    my_test_2(1)
    # my_test_3()
