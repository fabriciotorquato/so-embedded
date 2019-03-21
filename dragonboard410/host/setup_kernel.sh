cd /opt/db410

sudo apt-get install -y build-essential libncurses5-dev libssl-dev ccache abootimg android-tools-fastboot


if [ -e kernel ]
then
    echo "Kernel exists"
else
    echo "Downloading the Kernel repository."
    git clone http://git.linaro.org/landing-teams/working/qualcomm/kernel.git
    cd kernel
    git checkout origin/release/qcomlt-4.14 -b my-custom-4.14
fi