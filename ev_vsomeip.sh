#!/bin/bash

cd ~
cd ../../etc/ld.so.conf.d/
sudo apt update
sudo apt install vim
sudo touch libvsomeip.conf
echo "~/vsomeip/build/" > libvsomeip.conf

cd ~
sudo ldconfig
ldconfig -p | grep libvsomeip

