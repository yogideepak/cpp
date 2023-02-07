#!/bin/bash
sudo apt install cmake
sudo apt-get install libboost-all-dev
sudo apt install build-essential
sudo apt install git
git clone https://github.com/COVESA/vsomeip.git
cd vsomeip
mkdir build
cd build
cmake ..
make -j16
sudo make install
cd examples
make
sudo make install