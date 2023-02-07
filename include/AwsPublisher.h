#include <aws/crt/Api.h>
#include <aws/crt/StlAllocator.h>
#include <aws/crt/auth/Credentials.h>
#include <aws/crt/io/TlsOptions.h>

// #include <aws/iot/MqttClient.h>
//#include"final_cache.hpp"
#include "json.hpp"
#include <algorithm>
#include <aws/crt/UUID.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <regex>
#include <stdexcept>
#include <stdlib.h>
#include <thread>

using namespace std;
// #include "configuration.h"
// using json = nlohmann::json;

#include "../aws-iot-device-sdk-cpp-v2/samples/utils/CommandLineUtils.h"
// #include "readjson.h"
using namespace Aws::Crt;



template<typename T> 
void publish (T connection, std::string message)
{
   
   //config obj;
    Utils::CommandLineUtils cmdUtils = Utils::CommandLineUtils();
    
    String topic = cmdUtils.GetCommandOrDefault("topic","vehicle/vin/state/current");
    
    

    // std::string abc =  "trunk : "  +p2.trunk+" "+ "level : " +p2.level+" "+ "speed : "+ p2.speed+ " "+"current_temp : "+p2.current_temp+" "+"ac : "+p2.ac+" "+"sun_roof_stste : "+p2.sun_roof_state + " "+"engne : "+p2.engine+" "+"hazard : "+ p2.hazard+" "+"min_temp : "+p2.min_temp+ " "+ "max_temp : "+p2.max_temp+ " "+"bonet : "+p2.bonet+ " "+"child_lock : "+ p2.child_lock + " "+ "door_fronr_left : "+p2.door_front_left + " " +"door_front_right : "+ p2.door_front_right+ " "+"door_rear_left : "+ p2.door_rear_left+ " "+"door_rear_right : "+ p2.door_rear_right + " "+"window_front_left : "+ p2.WFleft + " "+"window_front_right : "+ p2.WFright + " "+"window_rear_left : "+ p2.WRleft + " "+"window_rear_right : "+ p2.WRright + " "+"light"+ p2.lights + " "+"side_mirror_left : "+ p2.SMleft + " "+"side_mirror_right : "+ p2.SMrighi + " "+"sum_volt : "+ p2.sum_volt + " "+"current : "+p2.current+ " "+"temperature : "+p2.temperature+ " "+"voltage : "+ p2.voltage+ " "+"mode : "+p2.mode+ " "+"soc : "+p2.soc+ " "+"soh : "+ p2.soh+ " "+"defrost_front : "+p2.defrost_front+ " " +"defrost_rear : "+ p2.defrost_rear+ " "+"air_circulation : "+p2.air_circulation+ " "+"ac_state : "+p2.HFac_state+ " "+"ac_vent_flow : "+p2.HFac_vent_flow+ " "+"temperature : "+p2.HFtemperature+ " "+"ac_state : "+p2.HRac_state+ " "+"ac_vent_flow : "+ p2.HRac_vent_flow+ " "+"temperature : "+ p2.HRtemperature+ " "+"current_location_long : "+ p2.current_location_long+ " "+"current_location_lat : "+p2.current_location_lat+ " "+"d_long : "+p2.d_long+ " "+"d_lat : "+p2.d_lat+ " "+"s_long : "+p2.s_long+ " "+"s_lat : "+p2.s_lat+ " "+"g_long : "+p2.g_long+ " "+"g_lat : "+ p2.g_lat+ " "+"radius : "+p2.radius;
    
    String messagePayload = cmdUtils.GetCommandOrDefault("message", message.c_str() );      //abc.c_str()
    
    // String messagePayload = cmdUtils.GetCommandOrDefault("message", abc.c_str());

   
    std::mutex receiveMutex;
        std::condition_variable receiveSignal;
        uint32_t receivedCount = 0;

        
    while (true)
    {
        ByteBuf payload = ByteBufFromArray((const uint8_t *)messagePayload.data(), messagePayload.length());

        auto onPublishComplete = [](Mqtt::MqttConnection &, uint16_t, int) {};
        connection->Publish(topic.c_str(), AWS_MQTT_QOS_AT_LEAST_ONCE, false, payload, onPublishComplete);
        

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
    
    {
            std::unique_lock<std::mutex> receivedLock(receiveMutex);
            receiveSignal.wait(receivedLock, [&] { return receivedCount ; });
    }
}

