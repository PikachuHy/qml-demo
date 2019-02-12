git clone https://github.com/CMU-Perceptual-Computing-Lab/openpose.git
cd openpose
mkdir build && cd build
cmake ..
make -j
sudo apt install ffmpeg
cd ..
cd xsnet
bash run_server.sh


