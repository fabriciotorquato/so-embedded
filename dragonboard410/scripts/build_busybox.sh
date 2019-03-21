cd /home/$USER/Documents

wget https://busybox.net/downloads/busybox-1.30.1.tar.bz2

tar xfvj busybox-*.tar.bz2

cd busybox-*/

make defconfig

make

sudo cp busybox /bin/busybox