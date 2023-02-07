#!/bin/sh
sudo apt install cmake
sudo apt install git
sudo apt-get install libboost-all-dev
cd /home/devops/sdk
git clone http://172.22.246.36/connectivity-and-cloud/dev_team/final_cpp_aws_someip_app.git

cd final_cpp_aws_someip_app/
sudo rm -rf build/CMakeCache.txt
sudo sh ev_vsomeip.sh
sudo sh setup_vsomeip.sh
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
cd /home/devops/sdk
mkdir sdk-workspace
cd sdk-workspace/
git clone --recursive https://github.com/aws/aws-iot-device-sdk-cpp-v2.git
cd aws-iot-device-sdk-cpp-v2
git submodule update --init --recursive
cd ..
mkdir aws-iot-device-sdk-cpp-v2-build
cd aws-iot-device-sdk-cpp-v2-build/
cake -DCMAKE_INSTALL_PREFIX="/home/devops/sdk/sdk-workspace/" -DCMAKE_BUILD_TYPE="Debug" ../aws-iot-device-sdk-cpp-v2
cmake -DCMAKE_INSTALL_PREFIX="/home/devops/sdk/sdk-workspace/" -DCMAKE_BUILD_TYPE="Debug" ../aws-iot-device-sdk-cpp-v2
cmake --build . --target install

cp -r /home/devops/sdk/final_cpp_aws_someip_app /home/devops/sdk/sdk-workspace/
cd /home/devops/sdk/sdk-workspace/final_cpp_aws_someip_app/
cd build/
rm -rf CMakeCache.txt 
cmake -DCMAKE_PREFIX_PATH="/home/devops/sdk/sdk-workspace"  -DCMAKE_BUILD_TYPE="Debug" ..
cmake --build . --config "Debug"



