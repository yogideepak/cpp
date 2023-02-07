#!/bin/sh
git clone https://github.com/nlohmann/json.git
cd json/
mkdir build
cd build/
cmake .. -DJSON_BuildTests=On
cmake --build .
cd ..
cd single_include/
cd nlohmann/
sudo mv json.hpp /usr/include/



