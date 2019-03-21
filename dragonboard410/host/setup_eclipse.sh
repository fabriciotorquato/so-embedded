cd /opt/db410

sudo apt-get install -y openjdk-8-jdk

if [ -e eclipse ]
then
    echo "Eclipse exists."
else
    echo "Downloading the Eclipse IDE."
    wget "http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/2019-03/RC1/eclipse-testing-2019-03-RC1-linux-gtk-x86_64.tar.gz&r=1"
    mv *eclipse-testing-2019-03-RC1-linux-gtk-x86_64* eclipse.tar.gz
    tar xfv eclipse.tar.gz
    sudo ln -s /opt/db410/eclipse/eclipse /usr/bin/eclipse
fi

