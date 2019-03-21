cd /opt/db410


sudo apt-get install -y make build-essential autoconf libtool cmake pkg-config git python-dev swig3.0 libpcre3-dev nodejs-dev

if [ -e gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz ]
then
    echo "Cross-compiler exists."
else
    echo "Downloading the cross compiler."
    wget https://releases.linaro.org/components/toolchain/binaries/latest-7/aarch64-linux-gnu/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz
    tar -xvf gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz
    ln -s gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/ toolchain
fi