cd ..
mkdir sdk-workspace
cd sdk-workspace/
git clone --recursive https://github.com/aws/aws-iot-device-sdk-cpp-v2.git
cd aws-iot-device-sdk-cpp-v2
git submodule update --init --recursive
cd ..
mkdir aws-iot-device-sdk-cpp-v2-build
cd aws-iot-device-sdk-cpp-v2-build/
cmake -DCMAKE_INSTALL_PREFIX="$(pwd)/../sdk-workspace" -DCMAKE_BUILD_TYPE="Debug" ../aws-iot-device-sdk-cpp-v2

#cmake -DCMAKE_INSTALL_PREFIX="../" -DCMAKE_BUILD_TYPE="Debug" ../aws-iot-device-sdk-cpp-v2
cmake --build . --target install


cd ../../final_cpp_aws_someip_app/build/
rm -rf CMakeCache.txt 
cmake -DCMAKE_PREFIX_PATH="sdk-workspace"  -DCMAKE_BUILD_TYPE="Debug" ..
cmake --build . --config "Debug"
