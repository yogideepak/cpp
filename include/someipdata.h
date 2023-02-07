#ifndef SOMEIPDATA_H
#define SOMEIPDATA_H
//#include <QObject>
#include <vsomeip/vsomeip.hpp>
#include "ignition_pojo.h"
#include "soc_pojo.h"

class SomeIpData {

public:
   std::set<vsomeip::eventgroup_t> its_groups;
   SomeIpData();
   //SomeIpData(Ignition_pojo *ignition_pojo, SOC_Pojo *soc_pojo);

   bool init();
   void start();
   void stopIgnition();
   void stopSOC();
   void on_state(vsomeip::state_type_e _state);
   void on_ignition_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
   void on_soc_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
   void on_ignition_change(const std::shared_ptr<vsomeip::message> &_response);
   void on_soc_change(const std::shared_ptr<vsomeip::message> &_response);

private:
    std::shared_ptr<vsomeip::application> app_;
    bool use_tcp_;
    //Ignition_pojo * m_Ignition_pojo;
    //SOC_Pojo *m_SOC_pojo;
};

#endif // SOMEIPDATA_H
