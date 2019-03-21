sudo mkdir -p /opt/db410
sudo chown -R $USER:$(id -gn) /opt/db410

sudo apt-get install -y minicom
sudo apt-get install -y net-tools

sh setup_crosscompiler.sh
sh setup_kernel.sh
sh setup_eclipse.sh
sh setup_vsc.sh $1
sudo sh setup_nfs.sh $1