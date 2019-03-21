cd /home/$USER/Documents

git clone https://github.com/intel-iot-devkit/mraa.git

mkdir -p ./mraa/build

cd mraa/build

cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..

make

make install

sudo ldconfig /usr/local/lib
