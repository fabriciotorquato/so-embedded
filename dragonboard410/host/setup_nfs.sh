sudo apt-get install -y nfs-kernel-server

if [ -e /srv/nfs/db410nfs ]
then
    echo "Nfs directory exists"
else
    echo "Creating NFS directory."
    sudo mkdir /srv/nfs/
    sudo mkdir /srv/nfs/db410nfs
    sudo chown -R $USER:$(id -gn) /srv/nfs/db410nfs
    sudo su
    sudo echo "/srv/nfs/db410nfs 10.42.0.*(rw,no_root_squash,no_subtree_check)" > /etc/exports
    sudo service nfs-kernel-server restart
fi