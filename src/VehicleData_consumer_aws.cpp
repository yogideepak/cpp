#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include <csignal>
#endif
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <stdint.h>
#include "../include/proper_cache.hpp"
#include "serdes.hpp"

#include "cluster.h"

#include <vsomeip/vsomeip.hpp>

#include "sample-ids.hpp"

#include "AwsPublisher.h"
#include <pthread.h>
#include "../include/soc_pojo.h"
#include "ignition_pojo.h"
#include "gear_pojo.h"
#include "mode_pojo.h"
#include "accelerator_pojo.h"
#include "image_pojo.h"

using namespace std;
std::shared_ptr<Aws::Crt::Mqtt::MqttConnection> connection;
// Aws::Crt::Mqtt::MqttConnection *connection;
struct currentVehicleData{

        long dataId;    

        float timeStamp;

        float throttle;

        float brake;

        float steering;
        float longitudinalVelocity;
        float acceleration;
        float speed;
        float rpm;
    };
class VehicleDataSDV_Consumer
{
public:
    std::set<vsomeip::eventgroup_t> its_groups1,its_groups2,its_groups3,its_groups4,its_groups5,its_groups6;
    string abc;
    //string ignition_11,soc_11;
    VehicleDataSDV_Consumer(bool _use_tcp, stutCarValue carVal) : app_(vsomeip::runtime::get()->create_application()), use_tcp_(
                                                                                                                           _use_tcp),
                                                                  carValue(carVal)
    {
    }

    bool init()
    {
        if (!app_->init())
        {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        std::cout << "Client settings [protocol="
                  << (use_tcp_ ? "TCP" : "UDP")
                  << "]"
                  << std::endl;

        app_->register_state_handler(
            std::bind(&VehicleDataSDV_Consumer::on_state, this,
                      std::placeholders::_1));

        app_->register_message_handler(
            m_SOC_Service_Id, m_SOC_Instance_Id, vsomeip::ANY_METHOD,
            std::bind(&VehicleDataSDV_Consumer::on_soc_message, this,
                      std::placeholders::_1));
            
        app_->register_message_handler(
            m_Ignition_Service_Id, m_Ignition_Instance_Id, vsomeip::ANY_METHOD,
            std::bind(&VehicleDataSDV_Consumer::on_ignition_message, this,
                      std::placeholders::_1));

        app_->register_message_handler(
            m_gear_Service_Id, m_gear_Instance_Id, vsomeip::ANY_METHOD,
            std::bind(&VehicleDataSDV_Consumer::on_gear_message, this,
                      std::placeholders::_1));

        app_->register_message_handler(
            m_mode_Service_Id, m_mode_Instance_Id, vsomeip::ANY_METHOD,
            std::bind(&VehicleDataSDV_Consumer::on_mode_message, this,
                      std::placeholders::_1));

        app_->register_message_handler(
            m_acc_Service_Id, m_acc_Instance_Id, vsomeip::ANY_METHOD,
            std::bind(&VehicleDataSDV_Consumer::on_acc_message, this,
                      std::placeholders::_1));                            

        app_->register_availability_handler(m_SOC_Service_Id, m_SOC_Instance_Id,
                                            std::bind(&VehicleDataSDV_Consumer::on_soc_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        app_->register_availability_handler(m_Ignition_Service_Id, m_Ignition_Instance_Id,
                                            std::bind(&VehicleDataSDV_Consumer::on_ignition_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        
        app_->register_availability_handler(m_mode_Service_Id, m_mode_Instance_Id,
                                            std::bind(&VehicleDataSDV_Consumer::on_mode_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        app_->register_availability_handler(m_gear_Service_Id, m_gear_Instance_Id,
                                            std::bind(&VehicleDataSDV_Consumer::on_gear_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));                                              
        
        app_->register_availability_handler(m_acc_Service_Id, m_acc_Instance_Id,
                                            std::bind(&VehicleDataSDV_Consumer::on_acc_availability,
                                                      this,
                                                      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


        // std::set<vsomeip::eventgroup_t> its_groups;
        its_groups1.insert(m_SOC_EventGroup_Id);
        app_->request_event(
            m_SOC_Service_Id,
            m_SOC_Instance_Id,
            m_SOC_Event_Id,
            its_groups1,
            vsomeip::event_type_e::ET_FIELD);
        app_->subscribe(m_SOC_Service_Id, m_SOC_Instance_Id, m_SOC_EventGroup_Id);


        its_groups2.insert(m_Ignition_EventGroup_Id);
        app_->request_event(
            m_Ignition_Service_Id,
            m_Ignition_Instance_Id,
            m_Ignition_Event_Id,
            its_groups2,
            vsomeip::event_type_e::ET_FIELD);
        app_->subscribe(m_Ignition_Service_Id, m_Ignition_Instance_Id, m_Ignition_EventGroup_Id);

        its_groups3.insert(m_gear_EventGroup_Id);
        app_->request_event(
            m_gear_Service_Id,
            m_gear_Instance_Id,
            m_gear_Event_Id,
            its_groups3,
            vsomeip::event_type_e::ET_FIELD);
        app_->subscribe(m_gear_Service_Id, m_gear_Instance_Id, m_gear_EventGroup_Id);
        
        its_groups4.insert(m_mode_EventGroup_Id);
        app_->request_event(
            m_mode_Service_Id,
            m_mode_Instance_Id,
            m_mode_Event_Id,
            its_groups4,
            vsomeip::event_type_e::ET_FIELD);
        app_->subscribe(m_mode_Service_Id, m_mode_Instance_Id, m_mode_EventGroup_Id);

        its_groups5.insert(m_acc_EventGroup_Id);
        app_->request_event(
            m_acc_Service_Id,
            m_acc_Instance_Id,
            m_acc_Event_Id,
            its_groups5,
            vsomeip::event_type_e::ET_FIELD);
        app_->subscribe(m_acc_Service_Id, m_acc_Instance_Id, m_acc_EventGroup_Id);

        return true;
    }

    void start()
    {
        app_->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    /*
     * Handle signal to shutdown
     */
    void SOC_stop()
    {
        app_->clear_all_handler();
        app_->unsubscribe(m_SOC_Service_Id, m_SOC_Instance_Id, m_SOC_EventGroup_Id);
        app_->release_event(m_SOC_Service_Id, m_SOC_Instance_Id, m_SOC_Event_Id);
        app_->release_service(m_SOC_Service_Id, m_SOC_Instance_Id);
        app_->stop();
    }

    void Ignition_stop()
    {
        app_->clear_all_handler();
        app_->unsubscribe(m_Ignition_Service_Id, m_Ignition_Instance_Id, m_Ignition_EventGroup_Id);
        app_->release_event(m_Ignition_Service_Id, m_Ignition_Instance_Id, m_Ignition_Event_Id);
        app_->release_service(m_Ignition_Service_Id, m_Ignition_Instance_Id);
        app_->stop();
    }

    void gear_stop()
    {
        app_->clear_all_handler();
        app_->unsubscribe(m_gear_Service_Id, m_gear_Instance_Id, m_gear_EventGroup_Id);
        app_->release_event(m_gear_Service_Id, m_gear_Instance_Id, m_gear_Event_Id);
        app_->release_service(m_gear_Service_Id, m_gear_Instance_Id);
        app_->stop();
    }

    void mode_stop()
    {
        app_->clear_all_handler();
        app_->unsubscribe(m_mode_Service_Id, m_mode_Instance_Id, m_mode_EventGroup_Id);
        app_->release_event(m_mode_Service_Id, m_mode_Instance_Id, m_mode_Event_Id);
        app_->release_service(m_mode_Service_Id, m_mode_Instance_Id);
        app_->stop();
    }

    void acc_stop()
    {
        app_->clear_all_handler();
        app_->unsubscribe(m_acc_Service_Id, m_acc_Instance_Id, m_acc_EventGroup_Id);
        app_->release_event(m_acc_Service_Id, m_acc_Instance_Id, m_acc_Event_Id);
        app_->release_service(m_acc_Service_Id, m_acc_Instance_Id);
        app_->stop();
    }
#endif

    void on_state(vsomeip::state_type_e _state)
    {
        if (_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            app_->request_service(m_SOC_Service_Id, m_SOC_Instance_Id);
            app_->request_service(m_Ignition_Service_Id, m_Ignition_Instance_Id);
            app_->request_service(m_gear_Service_Id, m_gear_Instance_Id);
            app_->request_service(m_mode_Service_Id, m_mode_Instance_Id);
            app_->request_service(m_acc_Service_Id, m_acc_Instance_Id);


        }
    }

    void on_soc_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;
                  std::cout <<"service id soc: " << m_SOC_Service_Id << std::endl;
    }


    void on_ignition_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout<<"On IGN Availabily"<<std::endl;
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;
                  std::cout <<"service id ignition: " << m_Ignition_Service_Id << std::endl;
    }

        void on_gear_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;
                  std::cout <<"service id gear: " << m_gear_Service_Id << std::endl;
    }

        void on_mode_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;
                  std::cout <<"service id mode: " << m_mode_Service_Id << std::endl;
    }

        void on_acc_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
    {
        std::cout << "Service ["
                  << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                  << "] is "
                  << (_is_available ? "available." : "NOT available.")
                  << std::endl;
                  std::cout <<"service id acc: " << m_acc_Service_Id << std::endl;
    }


    void setCarPropValue(string key, string value)
    {
        // switch (key)
        // {
        // case 'engine':
        //   p1.engine = value;
        //   break;
        // }

        if (key == "ignition")
        {

            // stutCarValue p3;
            //carValue.engine = value;
            p1.engine = value;
            //ignition_11 = value;
            igni_1 = value;
            cout << "ignition=" << carValue.engine << endl;
            cout << "ignition_value=" << value << endl;
        }
        else if (key == "soc")
        {

            // stutCarValue p3;
            //carValue.engine = value;
            p1.soc = value;
            //soc_11= value;
            soc_1=value;
            cout << "soc=" << carValue.engine << endl;
            cout << "soc_value=" << value << endl;
        }
        else if (key == "mode")
        {

            // stutCarValue p3;
            //carValue.engine = value;
            p1.drive_mode = value;
            //soc_11= value;
            drive_mode_1=value;
            cout << "drive_mode_1=" << carValue.drive_mode << endl;
            cout << "drive_mode_1=" << value << endl;
        }
        else if (key == "acc")
        {

            // stutCarValue p3;
            //carValue.engine = value;
            p1.speed = value;
            //soc_11= value;
            acceleration_1= value;
            cout << "acc=" << carValue.speed << endl;
            cout << "acc=" << value << endl;
        }
         else if (key == "gear")
        {

            // stutCarValue p3;
            //carValue.engine = value;
            p1.gear = value;
            //soc_11= value;
           gear_1 =value;
            cout << "gear=" << carValue.gear << endl;
            cout << "gear=" << value << endl;
        }
        else if (key == "RPM")
        {
           cout << "In Rpm loop" << endl;
            // stutCarValue p3;
            //carValue.engine = value;
            //p1.gear = value;
            //soc_11= value;
           //RPM_1 =value;
           RPM_1 = value;
            //cout << "RPM=" << carValue.gear << endl;
            cout << "RPM=" << RPM_1 << endl;
        }
    }



    void on_soc_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        its_message << "Received a notification for Event from Vehicle Data SDV ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_service() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_instance() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_method() << "] to Client/Session ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_client() << "/"
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_session()
                    << std::dec << its_payload->get_length()
                    << "]" << std::endl;
        std::cout << "Soc done massage" << endl;

        int SOC  = (int)its_payload->get_data()[0];
        
        its_message << " SOC: " << SOC;

        std::cout << its_message.str() << std::endl;
        setCarPropValue("soc",to_string(SOC));
       
        //  std::shared_ptr<vsomeip::payload> its_payload =
        // _response->get_payload();
        // its_message << "(" << std::dec << its_payload->get_length() << " ";
        // for (uint32_t i = 0; i < its_payload->get_length(); ++i)
        // {
        //     its_message << std::hex << std::setw(2) << std::setfill('0')

        //         << "ing   = " << (int)(its_payload->get_data()[i]);
            
    //         std::ifstream f("cardata.json");
    // json data = json::parse(f);

    // Data d;

    // CarStatusParse objCarStatusParse;
    // objCarStatusParse = setCarData(data);
    //         getCarData(objCarStatusParse,to_string((int)its_payload->get_data()[i]));
    //         // convert data to string
             //setCarPropValue("engine", to_string((int)its_payload->get_data()[i]));
        //ing_1 = to_string((int)its_payload->get_data()[i]);
        }


    void on_ignition_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        its_message << "Received a notification for Event from Vehicle Data SDV ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_service() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_instance() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_method() << "] to Client/Session ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_client() << "/"
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_session()
                    << std::dec << its_payload->get_length()
                    << "]" << std::endl;
        std::cout << "Ignition done massage" << endl;

        int ignition  = (int)its_payload->get_data()[0];
        
        its_message << " Ignition: " << ignition;
        std::cout << its_message.str() << std::endl;
        setCarPropValue("ignition",to_string(ignition));
        //  std::shared_ptr<vsomeip::payload> its_payload =
        // _response->get_payload();
        // its_message << "(" << std::dec << its_payload->get_length() << " ";
        // for (uint32_t i = 0; i < its_payload->get_length(); ++i)
        // {
        //     its_message << std::hex << std::setw(2) << std::setfill('0')

        //         << "ing   = " << (int)(its_payload->get_data()[i]);
            
    //         std::ifstream f("cardata.json");
    // json data = json::parse(f);

    // Data d;

    // CarStatusParse objCarStatusParse;
    // objCarStatusParse = setCarData(data);
    //         getCarData(objCarStatusParse,to_string((int)its_payload->get_data()[i]));
    //         // convert data to string
             //setCarPropValue("engine", to_string((int)its_payload->get_data()[i]));
        //ing_1 = to_string((int)its_payload->get_data()[i]);
      //  }
        // std::cout << its_message.str() << std::endl;
        // std::cout << "out its massage" << endl;

        // setCarPropValue("engine",its_payload->get_data()[i]);

        // if (_response->get_client() == 0)
        // {
        //     if ((its_payload->get_length() % 5) == 0)
        //     {
        //         std::shared_ptr<vsomeip::message> its_get = vsomeip::runtime::get()->create_request();
        //         its_get->set_service(SAMPLE_SERVICE_ID);
        //         its_get->set_instance(SAMPLE_INSTANCE_ID);
        //         its_get->set_method(SAMPLE_GET_METHOD_ID);
        //         its_get->set_reliable(use_tcp_);
        //         app_->send(its_get);
        //     }

        //     if ((its_payload->get_length() % 8) == 0)
        //     {
        //         std::shared_ptr<vsomeip::message> its_set = vsomeip::runtime::get()->create_request();
        //         its_set->set_service(SAMPLE_SERVICE_ID);
        //         its_set->set_instance(SAMPLE_INSTANCE_ID);
        //         its_set->set_method(SAMPLE_SET_METHOD_ID);
        //         its_set->set_reliable(use_tcp_);

        //         const vsomeip::byte_t its_data[] = {0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
        //                                             0x48, 0x49, 0x50, 0x51, 0x52};
        //         std::shared_ptr<vsomeip::payload> its_set_payload = vsomeip::runtime::get()->create_payload();
        //         its_set_payload->set_data(its_data, sizeof(its_data));
        //         its_set->set_payload(its_set_payload);
        //         app_->send(its_set);
        //     }
        // }

        //  its_payload->get_length();
        // its_message << "(" << std::dec << its_payload->get_length() << ") ";

        // int Gear = (uint8_t)its_payload->get_data()[0];
        // int Drive = (int)its_payload->get_data()[1];
        // int Speed = (int)its_payload->get_data()[2];

        // setCarPropValue("Drive", to_string(Drive));

        // its_message
        //     << " Gear: " << Gear << " Drive: " << Drive << " Speed: " << Speed;
        // std::cout << its_message.str() << std::endl;

        // // TODO: Call publish from here
        // // publish(connection, its_message.str());

        // switch (Drive)
        // {
        // case P:
        //     std::cout << "Mode: P: " << std::endl;
        //     break;
        // case R:
        //     std::cout << "Mode: R " << std::endl;
        //     break;
        // case D:
        //     std::cout << "Mode: D: " << std::endl;
        //     break;
        // case N:
        //     std::cout << "Mode: N: " << std::endl;
        //     break;
     }

        void on_gear_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        its_message << "Received a notification for Event from Vehicle Data SDV ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_service() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_instance() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_method() << "] to Client/Session ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_client() << "/"
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_session()
                    << std::dec << its_payload->get_length()
                    << "]" << std::endl;
        std::cout << "gear done massage" << endl;

        signed short gear  = (signed short)its_payload->get_data()[0];
        std::cout << " gear111111: " << gear << std::endl;
        its_message << " gear: " << gear;
        
        std::cout << its_message.str() << std::endl;
        setCarPropValue("gear",to_string(gear));
    
    }


        void on_mode_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        std::cout<<"IN DRIVE MODE...."<<endl;
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        its_message << "Received a notification for Event from Vehicle Data SDV ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_service() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_instance() << "."
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_method() << "] to Client/Session ["
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_client() << "/"
                    << std::setw(4) << std::setfill('0') << std::hex
                    << _response->get_session()
                    << std::dec << its_payload->get_length()
                    << "]" << std::endl;
        std::cout << "mode done massage" << endl;

        int mode  = (int)its_payload->get_data()[0];
        
        its_message << " mode: " << mode;

        std::cout << its_message.str() << std::endl;
        setCarPropValue("mode",to_string(mode));
    
    }

    void on_acc_message(const std::shared_ptr<vsomeip::message> &_response)
    {
        currentVehicleData D1;
        std::stringstream its_message;
        std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
        std::vector<vsomeip_v3::byte_t> its_payload_data;
        for(vsomeip_v3::length_t i=0;i<its_payload->get_length();i++){
            its_payload_data.push_back(its_payload->get_data()[i]);
        }
        its_message << "Received a notification for Event from Vehicle Data SDV ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_service() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_instance() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_method() << "] to Client/Session ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_client() << "/"
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_session()
            << std::dec << its_payload->get_length()
            << "]" << std::endl;
        std::cout << "acc done massage" << endl;
        serdes<currentVehicleData> se;
        D1 = se.deserialize(its_payload_data);
        //int acc  = (int)its_payload->get_data()[0];
        int acc = D1.speed;
        int RPM = D1.rpm;
        its_message << " acc: " << acc;
        its_message << " RPM: " << RPM;
        std::cout << its_message.str() << std::endl;
        foo=D1.rpm;
        setCarPropValue("acc",to_string(acc));
        setCarPropValue("RPM",to_string(RPM));
        
    }

private:
    std::shared_ptr<vsomeip::application> app_;
    bool use_tcp_;
    stutCarValue carValue;
};

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
VehicleDataSDV_Consumer *vdatasdv_ptr(nullptr);
void handle_signal(int _signal)
{
    if (vdatasdv_ptr != nullptr &&
        (_signal == SIGINT || _signal == SIGTERM))
        {vdatasdv_ptr->SOC_stop();
        vdatasdv_ptr->Ignition_stop();}
}
#endif

void scheduled_publish()
{

    // config obj;
    Utils::CommandLineUtils cmdUtils = Utils::CommandLineUtils();

    String topic = cmdUtils.GetCommandOrDefault("topic", "vehicle/vin/state/current");

    std::mutex receiveMutex;
    std::condition_variable receiveSignal;
    uint32_t receivedCount = 0;
 while (true)
    {
    const json j1{p1};
    const auto s1 = j1.dump(4);
    // cout << s1;
    std::string payload_data = s1;
    // std::string abc =  "trunk : "  +p2.trunk+" "+ "level : " +p2.level+" "+ "speed : "+ p2.speed+ " "+"current_temp : "+p2.current_temp+" "+"ac : "+p2.ac+" "+"sun_roof_stste : "+p2.sun_roof_state + " "+"engne : "+p2.engine+" "+"hazard : "+ p2.hazard+" "+"min_temp : "+p2.min_temp+ " "+ "max_temp : "+p2.max_temp+ " "+"bonet : "+p2.bonet+ " "+"child_lock : "+ p2.child_lock + " "+ "door_fronr_left : "+p2.door_front_left + " " +"door_front_right : "+ p2.door_front_right+ " "+"door_rear_left : "+ p2.door_rear_left+ " "+"door_rear_right : "+ p2.door_rear_right + " "+"window_front_left : "+ p2.WFleft + " "+"window_front_right : "+ p2.WFright + " "+"window_rear_left : "+ p2.WRleft + " "+"window_rear_right : "+ p2.WRright + " "+"light"+ p2.lights + " "+"side_mirror_left : "+ p2.SMleft + " "+"side_mirror_right : "+ p2.SMrighi + " "+"sum_volt : "+ p2.sum_volt + " "+"current : "+p2.current+ " "+"temperature : "+p2.temperature+ " "+"voltage : "+ p2.voltage+ " "+"mode : "+p2.mode+ " "+"soc : "+p2.soc+ " "+"soh : "+ p2.soh+ " "+"defrost_front : "+p2.defrost_front+ " " +"defrost_rear : "+ p2.defrost_rear+ " "+"air_circulation : "+p2.air_circulation+ " "+"ac_state : "+p2.HFac_state+ " "+"ac_vent_flow : "+p2.HFac_vent_flow+ " "+"temperature : "+p2.HFtemperature+ " "+"ac_state : "+p2.HRac_state+ " "+"ac_vent_flow : "+ p2.HRac_vent_flow+ " "+"temperature : "+ p2.HRtemperature+ " "+"current_location_long : "+ p2.current_location_long+ " "+"current_location_lat : "+p2.current_location_lat+ " "+"d_long : "+p2.d_long+ " "+"d_lat : "+p2.d_lat+ " "+"s_long : "+p2.s_long+ " "+"s_lat : "+p2.s_lat+ " "+"g_long : "+p2.g_long+ " "+"g_lat : "+ p2.g_lat+ " "+"radius : "+p2.radius;

    String messagePayload = cmdUtils.GetCommandOrDefault("message", payload_data.c_str()); // abc.c_str()

    //  String messagePayload = cmdUtils.GetCommandOrDefault("message", payload_data2.c_str());
    // String messagePayload = cmdUtils.GetCommandOrDefault("message", abc.c_str());
    cout << messagePayload;

    // std::mutex receiveMutex;
    // std::condition_variable receiveSignal;
    // uint32_t receivedCount = 0;

    // while (true)
    // {
        ByteBuf payload = ByteBufFromArray((const uint8_t *)messagePayload.data(), messagePayload.length());

        auto onPublishComplete = [](Mqtt::MqttConnection &, uint16_t, int) {};
        connection->Publish(topic.c_str(), AWS_MQTT_QOS_AT_LEAST_ONCE, false, payload, onPublishComplete);

        cout << "DONE11122222";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        cout << "XXXXXXXXXXX" << endl;
    }

    {
        std::unique_lock<std::mutex> receivedLock(receiveMutex);
        receiveSignal.wait(receivedLock, [&]
                           { return receivedCount; });
    }
}

int main(int argc, char *argv[])
{
    
    
    
    //      bool use_tcp = true;

    //     std::string tcp_enable("--tcp");
    //     std::string udp_enable("--udp");

    //     // int i = 1;
    //     // while (i < argc)
    //     // {
    //     //     if (tcp_enable == argv[i])
    //     //     {
    //     //         use_tcp = true;
    //     //     }
    //     //     else if (udp_enable == argv[i])
    //     //     {
    //     //         use_tcp = false;
    //     //     }
    //     //     i++;
    //     // }

    //     // use_tcp = true;

    //     VehicleDataSDV_Consumer vdatasdv(use_tcp);
    // #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    //     vdatasdv_ptr = &vdatasdv;
    //     signal(SIGINT, handle_signal);
    //     signal(SIGTERM, handle_signal);
    // #endif

    //     if (vdatasdv.init())
    //     {
    //         vdatasdv.start();
    //         // return 0;
    //     }

    // }

    //     bool use_tcp = true;

    //     std::string tcp_enable("--tcp");
    //     std::string udp_enable("--udp");

    //     int i = 1;
    //     while (i < argc)
    //     {
    //         if (tcp_enable == argv[i])
    //         {
    //             use_tcp = true;
    //         }
    //         else if (udp_enable == argv[i])
    //         {
    //             use_tcp = false;
    //         }
    //         i++;
    //     }

    //     use_tcp = true;

    //     // VehicleDataSDV_Consumer std::thread thread_obj2(vdatasdv);(use_tcp,p1);

    //    VehicleDataSDV_Consumer vdatasdv(use_tcp);
    // #ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    //     vdatasdv_ptr = &vdatasdv;
    //     signal(SIGINT, handle_signal);
    //     signal(SIGTERM, handle_signal);
    // #endif
    //     // std::thread thread_obj2(vdatasdv.init());
    //     // std::thread thread_obj3(vdatasdv.start());
    //     // if(thread_obj2.detach())
    //     // {
    //     //     thread_obj3.detach();
    //     // }

    //     if (vdatasdv.init())
    //     {
    //         vdatasdv.start();
    //         // return 0;
    //     }
    //     cout<<"class value="<<vdatasdv.abc<<endl;
    // std::thread thread_obj2(vdatasdv);
    //  thread_obj2.detach();
    //  cout<<"after class thread"<<endl;

    const char **const_argv = (const char **)argv;

    /************************ Setup the Lib ****************************/
    /*
     * Do the global initialization for the API.
     */
    ApiHandle apiHandle;

    /*********************** Parse Arguments ***************************/
    Utils::CommandLineUtils cmdUtils = Utils::CommandLineUtils();

    // TODO: hard-code
    //  const char **const_argv = (const char **)argv;

    cmdUtils.SendArguments(const_argv, const_argv + argc);
    cmdUtils.StartLoggingBasedOnCommand(&apiHandle);

    String topic = cmdUtils.GetCommandOrDefault("topic", "vehicle/vin/state/current");

    // String privatekey = cmdUtils.RegisterCommand("key","/home/fev/c++ program/sdk-workspace/aws-iot-device-sdk-cpp-v2/samples/pub_sub/basic_pub_sub/certificates/private.pem.key");

    String clientId = cmdUtils.GetCommandOrDefault("client_id", String("test-") + Aws::Crt::UUID().ToString());

    /* Get a MQTT client connection from the command parser */
    connection = cmdUtils.BuildMQTTConnection();

    /*
     * In a real world application you probably don't want to enforce synchronous behavior
     * but this is a sample console application, so we'll just do that with a condition variable.
     */
    std::promise<bool> connectionCompletedPromise;
    std::promise<void> connectionClosedPromise;

    /*
     * This will execute when an MQTT connect has completed or failed.
     */
    auto onConnectionCompleted = [&](Mqtt::MqttConnection &, int errorCode, Mqtt::ReturnCode returnCode, bool)
    {
        if (errorCode)
        {
            fprintf(stdout, "Connection failed with error %s\n", ErrorDebugString(errorCode));
            connectionCompletedPromise.set_value(false);
        }
        else
        {
            fprintf(stdout, "Connection completed with return code %d\n", returnCode);
            connectionCompletedPromise.set_value(true);
        }
    };

    auto onInterrupted = [&](Mqtt::MqttConnection &, int error)
    { fprintf(stdout, "Connection interrupted with error %s\n", ErrorDebugString(error)); };

    auto onResumed = [&](Mqtt::MqttConnection &, Mqtt::ReturnCode, bool)
    { fprintf(stdout, "Connection resumed\n"); };

    /*
     * Invoked when a disconnect message has completed.
     */
    auto onDisconnect = [&](Mqtt::MqttConnection &)
    {
        {
            fprintf(stdout, "Disconnect completed\n");
            connectionClosedPromise.set_value();
        }
    };

    connection->OnConnectionCompleted = std::move(onConnectionCompleted);
    connection->OnDisconnect = std::move(onDisconnect);
    connection->OnConnectionInterrupted = std::move(onInterrupted);
    connection->OnConnectionResumed = std::move(onResumed);

    /*
     * Actually perform the connect dance.
     */
    fprintf(stdout, "Connecting...\n");
    if (!connection->Connect(clientId.c_str(), false /*cleanSession*/, 1000 /*keepAliveTimeSecs*/))
    {
        fprintf(stderr, "MQTT Connection failed with error %s\n", ErrorDebugString(connection->LastError()));
        exit(-1);
    }
    // cout << "111111111";

    // if(connectionCompletedPromise.get_future().get()){

    // cout << "DONE111111";

    std::ifstream f("cardata.json");
    json data = json::parse(f);

    Data d;

    CarStatusParse objCarStatusParse;
    objCarStatusParse = setCarData(data);
    // struct stutCarValue p1;

    // struct stutCarValue p2;
    getCarData(objCarStatusParse);
    // cout << "Test";
    // const json j1{p1};
    // const auto s1 =j1.dump(4);
    // cout << s1;

    // scheduled_publish();

    // std::thread thread_obj2(vdatasdv);
    //  thread_obj2.detach();

    std::thread thread_obj(scheduled_publish);
    thread_obj.detach();

    cout << "Main after thread" << endl;

    // cout << "in main func" << endl;

    // const json j1 { p2 };
    //  Get JSON object from Person
    // const auto s1 = j1.dump(4);         // Get JSON string with indentation (4 spaces)
    // std::cout << s1 << '\n';

    bool use_tcp = true;

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");

    // int i = 1;
    // while (i < argc)
    // {
    //     if (tcp_enable == argv[i])
    //     {
    //         use_tcp = true;
    //     }
    //     else if (udp_enable == argv[i])
    //     {
    //         use_tcp = false;
    //     }
    //     i++;
    // }

    // use_tcp = true;

    VehicleDataSDV_Consumer vdatasdv(use_tcp, p1);
#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    vdatasdv_ptr = &vdatasdv;
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
#endif

    if (vdatasdv.init())
    {
        vdatasdv.start();
        // return 0;
    }
    cout << "class value=" << vdatasdv.abc << endl;
    //cout << "class value=" << vdatasdv.ignition_11 << endl;
    //cout << "class value=" << vdatasdv.soc_11 << endl;
    // std::cout<< carValue;
}
