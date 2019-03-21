cd /opt/db410

if [ -e vstudio.deb ]
then
    echo "Visual Studio Code exists."
else
    echo "Downloading Visual Studio Code"
    wget "https://go.microsoft.com/fwlink/?LinkID=760868"
    mv *LinkID=760868* vstudio.deb
    sudo dpkg -i vstudio.deb
fi