#System Update
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade

#Dependencies
sudo apt-get install cmake
sudo apt-get install libsoc-dev

cd /home/$USER/Documents

#MRAA Library
git clone https://github.com/intel-iot-devkit/mraa.git
mkdir -p ./mraa/build
cd mraa/build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make
make install
sudo ldconfig /usr/local/lib

#Libraries
sudo apt-get install libupm-dev

#Setup for HDMI2VGA Converter
echo "xrandr --newmode aoc 23.75 640 664 720 800  480 483 487 500  -HSync +Vsync" >> /home/$USER/.profile
echo "xrandr --addmode HDMI-1 aoc" >> /home/$USER/.profile
echo "xrandr --output HDMI-1 --mode aoc" >> /home/$USER/.profile
echo "xset s off"  >> /home/$USER/.profile
echo "xset -dpms"  >> /home/$USER/.profile
echo "xset s noblank"  >> /home/$USER/.profile