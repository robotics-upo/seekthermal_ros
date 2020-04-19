#!/bin/bash

sudo apt-get install doxygen pkg-config debhelper cmake groff qt4-dev-tools -y

wget http://ftp.us.debian.org/debian/pool/main/libp/libpng/libpng12-0_1.2.50-2+deb8u3_amd64.deb

sudo dpkg -i libpng12-0_1.2.50-2+deb8u3_amd64.deb

rm libpng12-0_1.2.50-2+deb8u3_amd64.deb

git clone https://github.com/kralf/remake.git && mkdir -p remake/build && cd remake/build && cmake .. && make && sudo make install

git clone https://github.com/ethz-asl/libseekthermal.git && mkdir -p libseekthermal/build && cd libseekthermal/build && cmake .. && make && sudo make install

