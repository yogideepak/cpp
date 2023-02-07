steps to run application:-

install jsoncpp library:-

-install jsoncpp library git link(https://github.com/nlohmann/json.git).
-follow commands to install.
1. git clone https://github.com/nlohmann/json.git
2. mkdir build
3. cd build
4. cmake .. -DJSON_BuildTests=On
5. cmake --build .
6. ctest --output-on-failure

open single-include in that open nlohmann folder then run command on this path
sudo mv json.hpp /usr/include/


install vsomeip-

-Check gcc edition ?vsomeip Using the C++11, need gcc 4.8 And above ??
gcc -v
-install cmake?vsomeip Using the CMake Build system ??
sudo apt install cmake
-Install Boost
sudo apt-get install libboost-all-dev
-Install git
sudo apt install git
-Open source project download
git clone https://github.com/COVESA/vsomeip.git
-Open the project
cd vsomeip
-Compile the entire project
mkdir build
cd build
cmake ..
make


install aws-iot-device-sdk-cpp-v2:-

- Create a workspace directory to hold all the SDK files
     mkdir sdk-workspace
     cd sdk-workspace
- Clone the repository
     git clone --recursive https://github.com/aws/aws-iot-device-sdk-cpp-v2.git
- Ensure all submodules are properly updated
     cd aws-iot-device-sdk-cpp-v2
     git submodule update --init --recursive
     cd ..
- Make a build directory for the SDK. Can use any name.
- If working with multiple SDKs, using a SDK-specific name is helpful.
	mkdir aws-iot-device-sdk-cpp-v2-build
	cd aws-iot-device-sdk-cpp-v2-build
- Generate the SDK build files.
- -DCMAKE_INSTALL_PREFIX needs to be the absolute/full path to the directory.
-     (Example: "/Users/example/sdk-workspace/).
- -DCMAKE_BUILD_TYPE can be "Release", "RelWithDebInfo", or "Debug"
	cmake -DCMAKE_INSTALL_PREFIX="<absolute path to sdk-workspace>" -DCMAKE_BUILD_TYPE="Debug" ../aws-iot-device-sdk-cpp-v2
- Build and install the library. Once installed, you can develop with the SDK and run the samples
	cmake --build . --target install
	
	
open aws-workspace
git clone http://172.22.246.36/connectivity-and-cloud/dev_team/final_cpp_aws_someip_app.git
cd build
cmake -DCMAKE_PREFIX_PATH="<absolute path to sdk-workspace>" - //example - cmake -DCMAKE_PREFIX_PATH="/home/infl158/projects/Projets/aws-sdk/sdv/sdk-workspace" -
DCMAKE_BUILD_TYPE="Debug" ..

LD_LIBRARY_PATH=<path to build> VSOMEIP_CONFIGURATION=<path of json file> VSOMEIP_APPLICATION_NAME=client-sample ./basic-pub-sub --endpoint "a36o9z4m44q7dt-ats.iot.us-east-1.amazonaws.com" --ca_file "path to certificates b_AmazonRootCA1.pem" --cert "path to certificates" --key "path to certificates/b_private.pem.key"

example-
LD_LIBRARY_PATH=/home/infl158/projects/Projets/aws-sdk/sdv/sdk-workspace/build VSOMEIP_CONFIGURATION=../config/vsomeip-local-client.json VSOMEIP_APPLICATION_NAME=client-sample ./basic-pub-sub --endpoint "a36o9z4m44q7dt-ats.iot.us-east-1.amazonaws.com" --ca_file "/home/infl158/projects/Projets/aws-sdk/sdv/sdk-workspace/certificates/b_AmazonRootCA1.pem" --cert "/home/infl158/projects/Projets/aws-sdk/sdv/sdk-workspace/certificates/b_certificate.pem.crt" --key "/home/infl158/projects/Projets/aws-sdk/sdv/sdk-workspace/certificates/b_private.pem.key"
