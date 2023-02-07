cmake_minimum_required(VERSION 3.1)
# note: cxx-17 requires cmake 3.8, cxx-20 requires cmake 3.12
project(basic-pub-sub CXX)

file(GLOB SRC_FILES
       "src/VehicleData_consumer_aws.cpp"
       "../aws-iot-device-sdk-cpp-v2/samples/utils/CommandLineUtils.cpp"
       "../aws-iot-device-sdk-cpp-v2/samples/utils/CommandLineUtils.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14)

#set warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4068)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-long-long -pedantic -Werror)
endif ()

#find_package(aws-crt-cpp REQUIRED)
find_package(aws-crt-cpp REQUIRED )
target_link_libraries(${PROJECT_NAME} AWS::aws-crt-cpp)



#cmake_minimum_required (VERSION 2.8)
#project(prg1)
#set(CMAKE_CXX_FLAGS "-g -std=c++11")

find_package(vsomeip3 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
   ${Boost_INCLUDE_DIR}
   ${VSOMEIP_INCLUDE_DIRS}
)
include_directories(include)

#add_executable(VehicleData_producer ../src/VehicleData_producer.cpp)
#target_link_libraries(VehicleData_producer vsomeip3 ${Boost_LIBRARIES})


#add_executable(VehicleData_consumer_aws ../src/VehicleData_consumer.cpp)
target_link_libraries(${PROJECT_NAME} vsomeip3 ${Boost_LIBRARIES})
