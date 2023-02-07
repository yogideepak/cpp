
#include <boost/optional.hpp>
// #include "struct_mapping/struct_mapping.h"
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
using json = nlohmann::json;
using namespace std;

class Battery
{
  public:
    Battery() = default;
    virtual ~Battery() = default;

  private:
    std::string sum_volt;
    std::string current;
    std::string temperature;
    std::string voltage;
    std::string mode;
    std::string soc;
    std::string soh;

  public:
    const std::string &get_sum_volt() const { return sum_volt; }
    std::string &get_mutable_sum_volt() { return sum_volt; }
    void set_sum_volt(const std::string &value) { this->sum_volt = value; }

    const std::string &get_current() const { return current; }
    std::string &get_mutable_current() { return current; }
    void set_current(const std::string &value) { this->current = value; }

    const std::string &get_temperature() const { return temperature; }
    std::string &get_mutable_temperature() { return temperature; }
    void set_temperature(const std::string &value) { this->temperature = value; }

    const std::string &get_voltage() const { return voltage; }
    std::string &get_mutable_voltage() { return voltage; }
    void set_voltage(const std::string &value) { this->voltage = value; }

    const std::string &get_mode() const { return mode; }
    std::string &get_mutable_mode() { return mode; }
    void set_mode(const std::string &value) { this->mode = value; }

    const std::string &get_soc() const { return soc; }
    std::string &get_mutable_soc() { return soc; }
    void set_soc(const std::string &value) { this->soc = value; }

    const std::string &get_soh() const { return soh; }
    std::string &get_mutable_soh() { return soh; }
    void set_soh(const std::string &value) { this->soh = value; }
};

class Front
{
  public:
    Front() = default;
    virtual ~Front() = default;

  private:
    std::string ac_state;
    std::string ac_vent_flow;
    std::string temperature;

  public:
    const std::string &get_ac_state() const { return ac_state; }
    std::string &get_mutable_ac_state() { return ac_state; }
    void set_ac_state(const std::string &value) { this->ac_state = value; }

    const std::string &get_ac_vent_flow() const { return ac_vent_flow; }
    std::string &get_mutable_ac_vent_flow() { return ac_vent_flow; }
    void set_ac_vent_flow(const std::string &value) { this->ac_vent_flow = value; }

    const std::string &get_temperature() const { return temperature; }
    std::string &get_mutable_temperature() { return temperature; }
    void set_temperature(const std::string &value) { this->temperature = value; }
};

class Hvac
{
  public:
    Hvac() = default;
    virtual ~Hvac() = default;

  private:
    std::string defrost_front;
    std::string defrost_rear;
    std::string air_circulation;
    Front front;
    Front rear;

  public:
    const std::string &get_defrost_front() const { return defrost_front; }
    std::string &get_mutable_defrost_front() { return defrost_front; }
    void set_defrost_front(const std::string &value) { this->defrost_front = value; }

    const std::string &get_defrost_rear() const { return defrost_rear; }
    std::string &get_mutable_defrost_rear() { return defrost_rear; }
    void set_defrost_rear(const std::string &value) { this->defrost_rear = value; }

    const std::string &get_air_circulation() const { return air_circulation; }
    std::string &get_mutable_air_circulation() { return air_circulation; }
    void set_air_circulation(const std::string &value) { this->air_circulation = value; }

    const Front &get_front() const { return front; }
    Front &get_mutable_front() { return front; }
    void set_front(const Front &value) { this->front = value; }

    const Front &get_rear() const { return rear; }
    Front &get_mutable_rear() { return rear; }
    void set_rear(const Front &value) { this->rear = value; }
};

class Lights
{
  public:
    Lights() = default;
    virtual ~Lights() = default;

  private:
    std::string head;

  public:
    const std::string &get_head() const { return head; }
    std::string &get_mutable_head() { return head; }
    void set_head(const std::string &value) { this->head = value; }
};

class CurrentLocation
{
  public:
    CurrentLocation() = default;
    virtual ~CurrentLocation() = default;

  private:
    std::string current_location_long;
    std::string lat;

  public:
    const std::string &get_current_location_long() const { return current_location_long; }
    std::string &get_mutable_current_location_long() { return current_location_long; }
    void set_current_location_long(const std::string &value) { this->current_location_long = value; }

    const std::string &get_lat() const { return lat; }
    std::string &get_mutable_lat() { return lat; }
    void set_lat(const std::string &value) { this->lat = value; }
};

class Point
{
  public:
    Point() = default;
    virtual ~Point() = default;

  private:
    std::string g_lat;
    std::string g_long;

  public:
    const std::string &get_g_lat() const { return g_lat; }
    std::string &get_mutable_g_lat() { return g_lat; }
    void set_g_lat(const std::string &value) { this->g_lat = value; }

    const std::string &get_g_long() const { return g_long; }
    std::string &get_mutable_g_long() { return g_long; }
    void set_g_long(const std::string &value) { this->g_long = value; }
};

class Geofence
{
  public:
    Geofence() = default;
    virtual ~Geofence() = default;

  private:
    Point point;
    std::string radius;

  public:
    const Point &get_point() const { return point; }
    Point &get_mutable_point() { return point; }
    void set_point(const Point &value) { this->point = value; }

    const std::string &get_radius() const { return radius; }
    std::string &get_mutable_radius() { return radius; }
    void set_radius(const std::string &value) { this->radius = value; }
};

class DestLocation
{
  public:
    DestLocation() = default;
    virtual ~DestLocation() = default;

  private:
    std::string d_long;
    std::string d_lat;

  public:
    const std::string &get_d_long() const { return d_long; }
    std::string &get_mutable_d_long() { return d_long; }
    void set_d_long(const std::string &value) { this->d_long = value; }

    const std::string &get_d_lat() const { return d_lat; }
    std::string &get_mutable_d_lat() { return d_lat; }
    void set_d_lat(const std::string &value) { this->d_lat = value; }
};

class StartLocation
{
  public:
    StartLocation() = default;
    virtual ~StartLocation() = default;

  private:
    std::string s_long;
    std::string s_lat;

  public:
    const std::string &get_s_long() const { return s_long; }
    std::string &get_mutable_s_long() { return s_long; }
    void set_s_long(const std::string &value) { this->s_long = value; }

    const std::string &get_s_lat() const { return s_lat; }
    std::string &get_mutable_s_lat() { return s_lat; }
    void set_s_lat(const std::string &value) { this->s_lat = value; }
};

class Stop
{
  public:
    Stop() = default;
    virtual ~Stop() = default;

  private:
    std::string stop_long;
    std::string lat;

  public:
    const std::string &get_stop_long() const { return stop_long; }
    std::string &get_mutable_stop_long() { return stop_long; }
    void set_stop_long(const std::string &value) { this->stop_long = value; }

    const std::string &get_lat() const { return lat; }
    std::string &get_mutable_lat() { return lat; }
    void set_lat(const std::string &value) { this->lat = value; }
};

class Stops
{
  public:
    Stops() = default;
    virtual ~Stops() = default;

  private:
    std::vector<Stop> stops;

  public:
    const std::vector<Stop> &get_stops() const { return stops; }
    std::vector<Stop> &get_mutable_stops() { return stops; }
    void set_stops(const std::vector<Stop> &value) { this->stops = value; }
};

class Routes
{
  public:
    Routes() = default;
    virtual ~Routes() = default;

  private:
    DestLocation dest_location;
    StartLocation start_location;
    Stops stops;

  public:
    const DestLocation &get_dest_location() const { return dest_location; }
    DestLocation &get_mutable_dest_location() { return dest_location; }
    void set_dest_location(const DestLocation &value) { this->dest_location = value; }

    const StartLocation &get_start_location() const { return start_location; }
    StartLocation &get_mutable_start_location() { return start_location; }
    void set_start_location(const StartLocation &value) { this->start_location = value; }

    const Stops &get_stops() const { return stops; }
    Stops &get_mutable_stops() { return stops; }
    void set_stops(const Stops &value) { this->stops = value; }
};

class Location
{
  public:
    Location() = default;
    virtual ~Location() = default;

  private:
    CurrentLocation current_location;
    Routes routes;
    Geofence geofence;

  public:
    const CurrentLocation &get_current_location() const { return current_location; }
    CurrentLocation &get_mutable_current_location() { return current_location; }
    void set_current_location(const CurrentLocation &value) { this->current_location = value; }

    const Routes &get_routes() const { return routes; }
    Routes &get_mutable_routes() { return routes; }
    void set_routes(const Routes &value) { this->routes = value; }

    const Geofence &get_geofence() const { return geofence; }
    Geofence &get_mutable_geofence() { return geofence; }
    void set_geofence(const Geofence &value) { this->geofence = value; }
};

class SideMirror
{
  public:
    SideMirror() = default;
    virtual ~SideMirror() = default;

  private:
    std::string left;
    std::string right;

  public:
    const std::string &get_left() const { return left; }
    std::string &get_mutable_left() { return left; }
    void set_left(const std::string &value) { this->left = value; }

    const std::string &get_right() const { return right; }
    std::string &get_mutable_right() { return right; }
    void set_right(const std::string &value) { this->right = value; }
};

class Door
{
  public:
    Door() = default;
    virtual ~Door() = default;

  private:
    std::string door_front_left;
    std::string door_front_right;
    std::string door_rear_left;
    std::string door_rear_right;

  public:
    const std::string &get_door_front_left() const { return door_front_left; }
    std::string &get_mutable_door_front_left() { return door_front_left; }
    void set_door_front_left(const std::string &value) { this->door_front_left = value; }

    const std::string &get_door_front_right() const { return door_front_right; }
    std::string &get_mutable_door_front_right() { return door_front_right; }
    void set_door_front_right(const std::string &value) { this->door_front_right = value; }

    const std::string &get_door_rear_left() const { return door_rear_left; }
    std::string &get_mutable_door_rear_left() { return door_rear_left; }
    void set_door_rear_left(const std::string &value) { this->door_rear_left = value; }

    const std::string &get_door_rear_right() const { return door_rear_right; }
    std::string &get_mutable_door_rear_right() { return door_rear_right; }
    void set_door_rear_right(const std::string &value) { this->door_rear_right = value; }
};

class WindowFront
{
  public:
    WindowFront() = default;
    virtual ~WindowFront() = default;

  private:
    std::string left;
    std::string right;

  public:
    const std::string &get_left() const { return left; }
    std::string &get_mutable_left() { return left; }
    void set_left(const std::string &value) { this->left = value; }

    const std::string &get_right() const { return right; }
    std::string &get_mutable_right() { return right; }
    void set_right(const std::string &value) { this->right = value; }
};

class WindowRear
{
  public:
    WindowRear() = default;
    virtual ~WindowRear() = default;

  private:
    std::string left;
    std::string right;

  public:
    const std::string &get_left() const { return left; }
    std::string &get_mutable_left() { return left; }
    void set_left(const std::string &value) { this->left = value; }

    const std::string &get_right() const { return right; }
    std::string &get_mutable_right() { return right; }
    void set_right(const std::string &value) { this->right = value; }
};

class Window
{
  public:
    Window() = default;
    virtual ~Window() = default;

  private:
    WindowFront front;
    WindowRear rear;

  public:
    const WindowFront &get_front() const { return front; }
    WindowFront &get_mutable_front() { return front; }
    void set_front(const WindowFront &value) { this->front = value; }

    const WindowRear &get_rear() const { return rear; }
    WindowRear &get_mutable_rear() { return rear; }
    void set_rear(const WindowRear &value) { this->rear = value; }
};

class VehicleDoors
{
  public:
    VehicleDoors() = default;
    virtual ~VehicleDoors() = default;

  private:
    std::string child_lock;
    Door door;
    Window window;

  public:
    const std::string &get_child_lock() const { return child_lock; }
    std::string &get_mutable_child_lock() { return child_lock; }
    void set_child_lock(const std::string &value) { this->child_lock = value; }

    const Door &get_door() const { return door; }
    Door &get_mutable_door() { return door; }
    void set_door(const Door &value) { this->door = value; }

    const Window &get_window() const { return window; }
    Window &get_mutable_window() { return window; }
    void set_window(const Window &value) { this->window = value; }
};

class Data
{
  public:
    Data() = default;
    virtual ~Data() = default;

  private:
    std::string level;
    std::string speed;
    std::string trunk;
    std::string mileage;
    std::string trip;
    std::string drive_mode;
    std::string current_temp;
    std::string ac;
    std::string sun_roof_state;
    std::string engine;
    std::string hazard;
    std::string min_temp;
    std::string max_temp;
    std::string bonet;
    VehicleDoors vehicle_doors;
    Lights lights;
    SideMirror side_mirror;
    Battery battery;
    Hvac hvac;
    Location location;

  public:
    const std::string &get_level() const { return level; }
    std::string &get_mutable_level() { return level; }
    void set_level(const std::string &value) { this->level = value; }

    const std::string &get_speed() const { return speed; }
    std::string &get_mutable_speed() { return speed; }
    void set_speed(const std::string &value) { this->speed = value; }

    const std::string &get_trunk() const { return trunk; }
    std::string &get_mutable_trunk() { return trunk; }
    void set_trunk(const std::string &value) { this->trunk = value; }

        const std::string & get_mileage() const { return mileage; }
    std::string & get_mutable_mileage() { return mileage; }
    void set_mileage(const std::string & value) { this->mileage = value; }

    const std::string & get_trip() const { return trip; }
    std::string & get_mutable_trip() { return trip; }
    void set_trip(const std::string & value) { this->trip = value; }

    const std::string & get_drive_mode() const { return drive_mode; }
    std::string & get_mutable_drive_mode() { return drive_mode; }
    void set_drive_mode(const std::string & value) { this->drive_mode = value; }

    const std::string &get_current_temp() const { return current_temp; }
    std::string &get_mutable_current_temp() { return current_temp; }
    void set_current_temp(const std::string &value) { this->current_temp = value; }

    const std::string &get_ac() const { return ac; }
    std::string &get_mutable_ac() { return ac; }
    void set_ac(const std::string &value) { this->ac = value; }

    const std::string &get_sun_roof_state() const { return sun_roof_state; }
    std::string &get_mutable_sun_roof_state() { return sun_roof_state; }
    void set_sun_roof_state(const std::string &value) { this->sun_roof_state = value; }

    const std::string &get_engine() const { return engine; }
    std::string &get_mutable_engine() { return engine; }
    void set_engine(const std::string &value) { this->engine = value; }

    const std::string &get_hazard() const { return hazard; }
    std::string &get_mutable_hazard() { return hazard; }
    void set_hazard(const std::string &value) { this->hazard = value; }

    const std::string &get_min_temp() const { return min_temp; }
    std::string &get_mutable_min_temp() { return min_temp; }
    void set_min_temp(const std::string &value) { this->min_temp = value; }

    const std::string &get_max_temp() const { return max_temp; }
    std::string &get_mutable_max_temp() { return max_temp; }
    void set_max_temp(const std::string &value) { this->max_temp = value; }

    const std::string &get_bonet() const { return bonet; }
    std::string &get_mutable_bonet() { return bonet; }
    void set_bonet(const std::string &value) { this->bonet = value; }

    const VehicleDoors &get_vehicle_doors() const { return vehicle_doors; }
    VehicleDoors &get_mutable_vehicle_doors() { return vehicle_doors; }
    void set_vehicle_doors(const VehicleDoors &value) { this->vehicle_doors = value; }

    const Lights &get_lights() const { return lights; }
    Lights &get_mutable_lights() { return lights; }
    void set_lights(const Lights &value) { this->lights = value; }

    const SideMirror &get_side_mirror() const { return side_mirror; }
    SideMirror &get_mutable_side_mirror() { return side_mirror; }
    void set_side_mirror(const SideMirror &value) { this->side_mirror = value; }

    const Battery &get_battery() const { return battery; }
    Battery &get_mutable_battery() { return battery; }
    void set_battery(const Battery &value) { this->battery = value; }

    const Hvac &get_hvac() const { return hvac; }
    Hvac &get_mutable_hvac() { return hvac; }
    void set_hvac(const Hvac &value) { this->hvac = value; }

    const Location &get_location() const { return location; }
    Location &get_mutable_location() { return location; }
    void set_location(const Location &value) { this->location = value; }
};

class CarStatusParse
{
  public:
    CarStatusParse() = default;
    virtual ~CarStatusParse() = default;

  private:
    std::string id;
    std::string vin;
    std::string type;
    std::string sub_type;
    Data data;

  public:
    const std::string &get_id() const { return id; }
    std::string &get_mutable_id() { return id; }
    void set_id(const std::string &value) { this->id = value; }

    const std::string &get_vin() const { return vin; }
    std::string &get_mutable_vin() { return vin; }
    void set_vin(const std::string &value) { this->vin = value; }

    const std::string &get_type() const { return type; }
    std::string &get_mutable_type() { return type; }
    void set_type(const std::string &value) { this->type = value; }

    const std::string &get_sub_type() const { return sub_type; }
    std::string &get_mutable_sub_type() { return sub_type; }
    void set_sub_type(const std::string &value) { this->sub_type = value; }

    const Data &get_data() const { return data; }
    Data &get_mutable_data() { return data; }
    void set_data(const Data &value) { this->data = value; }
};

CarStatusParse setCarData(json p)
{

    CarStatusParse objCarStatusParse;
    // json p = &data;
    Data objData;
    VehicleDoors vd;
    Door dr;
    Window w;
    WindowFront wf;
    WindowRear wr;
    Battery b;
    Lights l;
    SideMirror sm;
    Hvac h;
    Front ff;
    Front fr;
    Location lo;
    CurrentLocation cl;
    Routes ro;
    DestLocation dl;
    StartLocation sl;
    // Stop *st;
    Geofence g;
    Point po;

    objCarStatusParse.set_id(p["id"]);
    objCarStatusParse.set_vin(p["vin"]);
    objCarStatusParse.set_type(p["type"]);
    objCarStatusParse.set_sub_type(p["sub_type"]);

    objData.set_level(p["data"]["level"]);
    objData.set_speed(p["data"]["speed"]);
    objData.set_trunk(p["data"]["trunk"]);
    objData.set_mileage(p["data"]["mileage"]);
    objData.set_trip(p["data"]["trip"]);
    objData.set_drive_mode(p["data"]["driveMode"]);
    objData.set_current_temp(p["data"]["current_temp"]);
    objData.set_ac(p["data"]["ac"]);
    objData.set_sun_roof_state(p["data"]["sun_roof_state"]);
    objData.set_engine(p["data"]["engine"]);
    objData.set_hazard(p["data"]["hazard"]);
    objData.set_min_temp(p["data"]["min_temp"]);
    objData.set_max_temp(p["data"]["max_temp"]);
    objData.set_bonet(p["data"]["bonet"]);

    vd.set_child_lock(p["data"]["vehicle_doors"]["child_lock"]);
    dr.set_door_front_left(p["data"]["vehicle_doors"]["door"]["door_front_left"]);
    dr.set_door_front_right(p["data"]["vehicle_doors"]["door"]["door_front_right"]);
    dr.set_door_rear_left(p["data"]["vehicle_doors"]["door"]["door_rear_left"]);
    dr.set_door_rear_right(p["data"]["vehicle_doors"]["door"]["door_rear_right"]);

    wf.set_left(p["data"]["vehicle_doors"]["window"]["front"]["left"]);
    wf.set_right(p["data"]["vehicle_doors"]["window"]["front"]["right"]);

    wr.set_left(p["data"]["vehicle_doors"]["window"]["rear"]["left"]);
    wr.set_right(p["data"]["vehicle_doors"]["window"]["rear"]["right"]);

    vd.set_door(dr);
    w.set_front(wf);
    w.set_rear(wr);
    vd.set_window(w);

    b.set_sum_volt(p["data"]["battery"]["sumVolt"]);
    b.set_current(p["data"]["battery"]["current"]);
    b.set_temperature(p["data"]["battery"]["temperature"]);
    b.set_voltage(p["data"]["battery"]["voltage"]);
    b.set_mode(p["data"]["battery"]["mode"]);
    b.set_soc(p["data"]["battery"]["soc"]);
    b.set_soh(p["data"]["battery"]["soh"]);

    l.set_head(p["data"]["lights"]["head"]);

    sm.set_left(p["data"]["side_mirror"]["left"]);
    sm.set_right(p["data"]["side_mirror"]["right"]);

    h.set_air_circulation(p["data"]["hvac"]["air_circulation"]);
    h.set_defrost_front(p["data"]["hvac"]["defrost_front"]);
    h.set_defrost_rear(p["data"]["hvac"]["defrost_rear"]);

    ff.set_ac_state(p["data"]["hvac"]["front"]["ac_state"]);
    ff.set_ac_vent_flow(p["data"]["hvac"]["front"]["ac_vent_flow"]);
    ff.set_temperature(p["data"]["hvac"]["front"]["temperature"]);
    h.set_front(ff);

    fr.set_ac_state(p["data"]["hvac"]["rear"]["ac_state"]);
    fr.set_ac_vent_flow(p["data"]["hvac"]["rear"]["ac_vent_flow"]);
    fr.set_temperature(p["data"]["hvac"]["rear"]["temperature"]);
    h.set_rear(fr);

    cl.set_current_location_long(p["data"]["location"]["current_location"]["long"]);
    cl.set_lat(p["data"]["location"]["current_location"]["lat"]);
    dl.set_d_long(p["data"]["location"]["routes"]["destLocation"]["long"]);
    dl.set_d_lat(p["data"]["location"]["routes"]["destLocation"]["lat"]);

    sl.set_s_long(p["data"]["location"]["routes"]["start_location"]["long"]);
    sl.set_s_lat(p["data"]["location"]["routes"]["start_location"]["lat"]);

    po.set_g_lat(p["data"]["location"]["geofence"]["point"]["lat"]);
    po.set_g_long(p["data"]["location"]["geofence"]["point"]["long"]);
    g.set_radius(p["data"]["location"]["geofence"]["radius"]);

    g.set_point(po);

    // st->set_sp_lat();

    // cout << "Setter : " <<  p["data"]["location"]["routes"]["stops"].find("long")[0] <<endl;

    // vector<Stop> stp;
    // Stops stps;
    // for (auto &elm : p["data"]["location"]["routes"]["stops"].items())
    // {
    //     nlohmann::json object = elm.value();

    //     Stop oStop;
    //     oStop.set_lat(object.at("lat"));
    //     oStop.set_stop_long(object.at("long"));
    //     stp.push_back(oStop);
    // }

    // stps.set_stops(stp);

    // ro.set_stops(stps);

    lo.set_geofence(g);
    ro.set_start_location(sl);
    ro.set_dest_location(dl);
    lo.set_routes(ro);
    lo.set_current_location(cl);

    objData.set_battery(b);
    objData.set_lights(l);
    objData.set_side_mirror(sm);
    objData.set_hvac(h);
    objData.set_vehicle_doors(vd);
    objData.set_location(lo);

    objCarStatusParse.set_data(objData);

    return objCarStatusParse;
}

std::string igni_1,soc_1,drive_mode_1,acceleration_1,gear_1,RPM_1,foo;

struct stutCarValue
{
    std::string id;
    std::string vin;
    std::string type;
    std::string sub_type;
    std::string trunk;
    std::string mileage;
    std::string trip;
    std::string drive_mode;
    std::string gear;
    std::string level;
    std::string speed;
    std::string rpm;
    std::string current_temp;
    std::string ac;
    std::string sun_roof_state;
    std::string engine;
    std::string hazard;
    std::string min_temp;
    std::string max_temp;
    std::string bonet;
    std::string child_lock;
    std::string door_front_left;
    std::string door_front_right;
    std::string door_rear_left;
    std::string door_rear_right;
    std::string WFleft;
    std::string WFright;
    std::string WRleft;
    std::string WRright;
    std::string lights;
    std::string SMleft;
    std::string SMright;
    std::string sum_volt;
    std::string current;
    std::string temperature;
    std::string voltage;
    std::string mode;
    std::string soc;
    std::string soh;
    std::string defrost_front;
    std::string defrost_rear;
    std::string air_circulation;
    std::string HFac_state;
    std::string HFac_vent_flow;
    std::string HFtemperature;
    std::string HRac_state;
    std::string HRac_vent_flow;
    std::string HRtemperature;
    std::string current_location_long;
    std::string current_location_lat;
    std::string d_long;
    std::string d_lat;
    std::string s_long;
    std::string s_lat;
    std::string g_long;
    std::string g_lat;
    std::string radius;
    //std::string arr;

}p1;

void to_json(json &j, const stutCarValue &p1)
{
    json _door=json{
    {"door_front_left",p1.door_front_left},
    {"door_front_right",p1.door_front_right},
    {"door_rear_left",p1.door_rear_left},
    {"door_rear_right",p1.door_rear_right}
  };
    json _front = json{
    {"left",p1.WFleft},
    {"right",p1.WFright}
   };
   json _rear= json{
    {"left",p1.WRleft},
    {"right",p1.WRright}
   };
    json _window =json{
    {"front",_front},
    {"rear",_rear}
   };
   json _vehicleDoors =json{
      {"child_lock",p1.child_lock},
      {"door",_door},
      {"window",_window}
   };
   json _lights ={
    {"head",p1.lights}
   };
   json _sidemirror ={
    {"left",p1.SMleft},
    {"right",p1.SMright}
   };
   json _battery ={
    {"sum_volt",p1.sum_volt},
    {"current",p1.current},
    {"temperature",p1.temperature},
    {"voltage",p1.voltage},
    {"mode",p1.mode},
    {"soc",p1.soc},
    {"soh",p1.soh}
   };
   json h_front ={
    {"ac_state",p1.HFac_state},
    {"ac_vent_flow",p1.HFac_vent_flow},
    {"temperature",p1.HFtemperature}
   };
   json h_rear ={
    {"ac_state",p1.HRac_state},
    {"ac_vent_flow",p1.HRac_vent_flow},
    {"temperature",p1.HRtemperature}
   };

   json _hvac ={
    {"defrost_front",p1.defrost_front},
    {"defrost_rear",p1.defrost_rear},
    {"air_circulation",p1.air_circulation},
    {"front",h_front},
    {"rear",h_rear}
   };
   json _currentloc ={
    {"lang",p1.current_location_long},
    {"lat",p1.current_location_lat}
   };
   json _dest_location ={
    {"lang",p1.d_long},
    {"lat",p1.d_lat}
   };
   json _start_location={
    {"lang",p1.s_long},
    {"lat",p1.s_lat}
   };
   json _routes ={
    {"dest_location",_dest_location},
    {"start_location",_start_location}
   };
     json _point ={
    {"lang",p1.g_long},
    {"lat",p1.g_lat}
   };
   json _geofence={
    {"point",_point},
    {"radius",p1.radius}
   };
   json _location ={
    {"current_location",_currentloc},
    {"routes",_routes},
    {"geofence",_geofence}
   };
  
   
   json _data ={
    {"level",p1.level},
    {"trunk",p1.trunk},
    {"mileage",p1.mileage},
    {"trip",p1.trip},
    {"drive_mode",p1.drive_mode},
    {"gear_mode",p1.gear},
    {"speed",p1.speed},
    {"rpm",p1.rpm},
    {"current_temp",p1.current_temp},
    {"ac",p1.ac},
    {"sun_roof_state",p1.sun_roof_state},
    {"engine",p1.engine},
    {"hazard",p1.hazard},
    {"min_temp",p1.min_temp},
    {"max_temp",p1.max_temp},
    {"bonet",p1.bonet},
    {"vehicle_doors",_vehicleDoors},
    //{"window",_window},
    {"lights",_lights},
    {"side_mirror",_sidemirror},
    {"battery",_battery},
    {"hvac",_hvac},
    {"location",_location},
    //{"binary",p1.arr}
    //{"geofence",_geofence}
   };


    j = json{
        {"id",p1.id},
        {"vin",p1.vin},
        {"type",p1.type},
        {"data",_data},

        // {"trunk", p1.trunk},
        // {"level", p1.level},
        // {"speed", p1.speed},
        // {"current_temp", p1.current_temp},
        // {"ac", p1.ac},
        // {"sun_roof_state", p1.sun_roof_state},
        // {"engine" , p1.engine},
        // {"hazard", p1.hazard},
        // {"min_temp",p1.min_temp},
        // {"max_temp",p1.max_temp},
        // {"bonet",p1.bonet},
        //{"child_lock",p1.child_lock},
        //{"vehicleDoors",_vehicleDoors},
        //{"window",_window},
        // {"door_front_left",p1.door_front_left},
        // {"door_front_right",p1.door_front_right},
        // {"door_rear_left",p1.door_rear_left},
        // {"door_rear_right",p1.door_rear_right},

        // {"window_front_left",p1.WFleft},
        // {"window_front_right",p1.WFright},
        // {"window_rear_left",p1.WRleft},
        // {"window_rear_right",p1.WRright},
        // {"lights",_lights},
       // {"lights",p1.lights},
        // {"side_mirror",_sidemirror},
        // {"side_mirror_left",p1.SMleft},
        // {"side_mirror_right",p1.SMright},
        // {"battery",_battery},
        // {"sum_volt",p1.sum_volt},
        // {"current",p1.current},
        // {"temperature",p1.temperature},
        // {"voltage",p1.voltage},
        // {"mode",p1.mode},
        // {"soc",p1.soc},
        // {"soh",p1.soh},
        // {"hvac",_hvac},
        // {"defrost_front",p1.defrost_front},
        // {"defrost_rear",p1.defrost_rear},
        // {"air_circulation",p1.air_circulation},
        // {"HFac_state",p1.HFac_state},
        // {"HFac_vent_flow",p1.HFac_vent_flow},
        // {"HFtemperature",p1.HFtemperature},
        // {"HRac_state",p1.HRac_state},
        // {"HRac_vent_flow",p1.HRac_vent_flow},
        // {"HRtemperature",p1.HRtemperature},
        // {"current_location_long",p1.current_location_long},
        // {"current_location_lat",p1.current_location_lat},
        // {"_location",_location},
        // {"d_long",p1.d_long},
        // {"d_lat",p1.d_lat},
        // {"s_long",p1.s_long},
        // {"s_lat",p1.s_lat},
        // {"geofence",_geofence}
        // {"g_long",p1.g_long},
        // {"g_lat",p1.g_lat},
        // {"radius",p1.radius}
        };
    
}
     
stutCarValue getCarData(CarStatusParse objCarStatusParse)
{
    Data d;

    p1.id=objCarStatusParse.get_id();
   // p1.id = gear_1;
    p1.vin=objCarStatusParse.get_vin();
    //p1.vin = acceleration_1;
    p1.type= objCarStatusParse.get_type();
    p1.sub_type= objCarStatusParse.get_sub_type();
    d = objCarStatusParse.get_data();

    cout<<"trunk="<<d.get_trunk()<<endl;
    p1.trunk = d.get_trunk();
    p1.mileage=d.get_mileage();
    p1.trip=d.get_trip();
    //p1.drive_mode=d.get_drive_mode();
    p1.drive_mode = drive_mode_1;
    p1.gear = gear_1;
    //p1.level = d.get_level();
    //p1.level = RPM_1;
    p1.level = foo;
    //p1.speed = d.get_speed();
    p1.speed = acceleration_1;
    std::cout<<"getCarData RPM_1"<<RPM_1<<std::endl;
    p1.rpm = RPM_1;
    std::cout<<"getCarData p1.rpm"<<p1.rpm<<std::endl;
    p1.current_temp = d.get_current_temp();
    p1.ac = d.get_ac();
    p1.sun_roof_state = d.get_sun_roof_state();
    //p1.engine = d.get_engine();
    p1.engine = igni_1;
    p1.hazard = d.get_hazard();
    p1.min_temp = d.get_min_temp();
    p1.max_temp = d.get_max_temp();
    p1.bonet = d.get_bonet();

    p1.child_lock = d.get_vehicle_doors().get_child_lock();

    p1.door_front_left = d.get_vehicle_doors().get_door().get_door_front_left();
    p1.door_front_right = d.get_vehicle_doors().get_door().get_door_front_right();
    p1.door_rear_left = d.get_vehicle_doors().get_door().get_door_rear_left();
    p1.door_rear_right = d.get_vehicle_doors().get_door().get_door_rear_right();

    p1.WFleft = d.get_vehicle_doors().get_window().get_front().get_left();
    p1.WFright = d.get_vehicle_doors().get_window().get_front().get_right();
    p1.WRleft = d.get_vehicle_doors().get_window().get_rear().get_left();
    p1.WRright = d.get_vehicle_doors().get_window().get_rear().get_right();

    p1.lights = d.get_lights().get_head();

    p1.SMleft = d.get_side_mirror().get_left();
    p1.SMright = d.get_side_mirror().get_right();

    p1.sum_volt = d.get_battery().get_sum_volt();
    p1.current = d.get_battery().get_current();
    p1.temperature = d.get_battery().get_temperature();
    p1.voltage = d.get_battery().get_voltage();
    p1.mode = d.get_battery().get_mode();
    //p1.soc = d.get_battery().get_soc();
    p1.soc=soc_1;
    p1.soh = d.get_battery().get_soh();

    p1.defrost_front = d.get_hvac().get_defrost_front();
    p1.defrost_rear = d.get_hvac().get_defrost_rear();
    p1.air_circulation = d.get_hvac().get_air_circulation();
    p1.HFac_state = d.get_hvac().get_front().get_ac_state();
    p1.HFac_vent_flow = d.get_hvac().get_front().get_ac_vent_flow();
    p1.HFtemperature = d.get_hvac().get_front().get_temperature();
    p1.HRac_state = d.get_hvac().get_rear().get_ac_state();
    p1.HRac_vent_flow = d.get_hvac().get_rear().get_ac_vent_flow();
    p1.HRtemperature = d.get_hvac().get_rear().get_temperature();

    p1.current_location_long = d.get_location().get_current_location().get_current_location_long();
    p1.current_location_lat = d.get_location().get_current_location().get_lat();
    p1.d_long = d.get_location().get_routes().get_dest_location().get_d_long();
    p1.d_lat = d.get_location().get_routes().get_dest_location().get_d_lat();
    p1.s_long = d.get_location().get_routes().get_start_location().get_s_long();
    p1.s_lat = d.get_location().get_routes().get_start_location().get_s_lat();

    // Stops g1 = d.get_location().get_routes().get_stops();

    // vector<Stop> v1 = g1.get_stops();

    // v1.shrink_to_fit();

    // for (int i = 0; i < v1.size(); i++)
    // cout << v1[i].get_lat() << " : " << v1[i].get_stop_long();

    p1.g_long = d.get_location().get_geofence().get_point().get_g_long();
    p1.g_lat = d.get_location().get_geofence().get_point().get_g_lat();
    p1.radius = d.get_location().get_geofence().get_radius();
    //p1.arr= "-119,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,50,0,0,0,50,8,6,0,0,0,30,63,-120,-79,0,0,0,1,115,82,71,66,0,-82,-50,28,-23,0,0,0,4,115,66,73,84,8,8,8,8,124,8,100,-120,0,0,17,126,73,68,65,84,104,-127,-19,-103,123,112,-108,-27,-67,-57,63,-17,125,47,-55,102,-77,-71,65,4,18,19,-110,67,-116,-91,28,8,-96,-25,-56,20,5,4,90,47,-116,-57,118,96,-58,113,-114,85,-47,-114,78,-89,-114,101,-22,113,-54,88,61,-22,105,-88,90,47,-83,-62,-87,-38,-127,30,14,-46,-42,106,123,84,-52,113,-28,-90,86,4,-119,114,-47,92,48,-127,112,-55,109,-109,108,118,-109,-35,125,-9,-67,-98,63,118,-9,61,68,80,-60,-42,-2,-43,103,-26,55,-5,-18,-66,-5,-18,-13,-3,62,-33,-33,-19,121,22,-2,62,-2,62,-66,-110,33,-4,-83,38,-22,-17,119,-125,-87,-44,-47,33,-37,-74,125,-106,101,77,-72,39,-53,50,-110,36,-11,-44,-44,-44,84,127,-39,-33,-1,74,-119,28,61,122,-44,-51,100,50,-104,-90,-119,97,24,-104,-90,-119,105,-102,88,-106,-123,-21,-70,89,0,-126,-128,-94,40,-56,-78,-116,-86,-86,100,50,25,36,73,-94,-72,-72,56,83,87,87,-25,-5,-94,115,125,37,68,-114,28,57,-30,-26,1,15,15,15,-45,-37,-37,-53,-32,-32,32,-90,105,18,10,-123,8,-121,-61,72,-110,52,-127,-116,36,73,-68,-1,-2,-5,92,122,-23,-91,44,90,-76,-120,120,60,78,111,111,47,115,-26,-52,-7,66,24,-27,-65,54,-119,-105,95,126,-39,-19,-24,-24,-96,-89,-89,-121,-127,104,-108,-111,-111,40,-121,14,29,98,116,36,78,117,77,13,-63,96,0,81,-111,-48,20,-107,80,-80,0,-97,79,-91,-13,72,39,-67,-89,6,88,-75,106,21,-82,36,-77,-26,-57,63,70,85,85,52,77,-93,-65,-65,-33,-99,52,105,-46,57,-55,-120,127,77,18,-65,-3,-19,111,-35,76,38,77,-37,39,-19,92,-78,-8,-78,-73,-58,-57,-29,92,-13,47,-41,125,-16,-52,115,-49,-18,-36,-72,-7,-65,48,77,-101,-8,88,-110,-111,-31,56,67,-47,33,-114,29,63,-59,-47,-98,83,-56,-78,-113,116,58,77,121,121,57,-81,-67,-66,-115,-47,-47,24,-15,-111,97,-12,116,-102,-1,120,-28,17,90,91,91,15,-1,-51,-120,28,63,126,-68,73,81,36,-6,-121,-93,-18,85,-41,94,-75,-13,103,-9,55,47,48,-52,12,83,-90,86,-58,-17,-70,-29,-5,11,-17,-68,-13,-5,-72,2,8,-94,-117,40,-127,-30,-45,48,109,-117,127,-1,-23,125,59,7,6,-94,-36,113,-57,29,92,125,-43,-75,92,-7,-99,-21,119,6,11,2,104,-110,76,-45,55,22,-20,19,101,-103,-1,124,-10,-7,-58,-65,25,-111,-10,-10,-10,125,-47,104,-108,37,-53,-106,-19,18,92,-105,73,23,-108,51,20,29,69,20,37,-110,-87,12,-114,101,-15,-77,39,127,-70,83,85,101,50,25,-125,-31,-95,24,-79,88,-116,-127,-127,-88,118,-4,88,15,93,93,93,-20,-22,56,-76,-53,114,28,28,-37,-63,52,77,-76,64,65,18,-96,-84,-94,-100,-106,-106,22,-9,43,39,-14,-101,-33,-4,-58,29,30,30,-28,-78,37,87,-20,68,-80,113,0,-53,-44,25,24,-24,-25,-105,-49,60,-35,104,91,38,-106,-29,32,10,34,-102,-26,-57,-79,109,-110,-55,52,-23,-76,-63,-113,-1,-19,-127,75,93,108,74,74,74,48,29,-37,-79,108,7,-41,117,113,93,23,73,-110,16,-112,48,77,-109,-39,-77,103,127,46,-122,-65,56,-40,-113,30,61,26,62,120,-16,67,-6,-121,-94,67,-72,54,-126,44,-111,78,36,21,-45,52,1,-8,-24,80,91,-103,-27,56,88,-74,-53,13,-33,-71,105,-95,-86,-54,100,12,3,89,-110,-112,101,-103,68,98,12,-45,52,-87,-88,-88,96,-61,67,-51,-105,-37,-114,67,85,-43,20,-122,-57,-110,-20,-8,-97,87,22,-54,-94,-116,36,41,28,56,112,-128,-50,-50,78,-77,-66,-66,94,57,27,-114,-65,72,-111,-97,-1,-4,-25,110,123,123,123,44,22,27,97,-63,-94,-123,-121,29,81,64,0,-18,-66,107,-51,63,91,-90,-119,-82,-21,24,41,3,-53,-74,112,108,19,28,-117,84,42,-123,109,89,-40,54,24,70,6,17,88,-69,118,45,-41,93,119,29,-122,97,32,73,18,5,5,69,84,94,80,-119,36,72,-8,-4,62,110,-69,-7,-69,57,-46,9,-71,-67,-67,-3,-84,46,-10,-91,-119,124,-12,-47,71,-18,-98,61,123,-48,-11,20,-13,-66,-15,79,59,5,17,36,81,-60,5,102,-4,67,53,-67,-67,3,-40,-114,-125,-98,74,-29,-40,14,-126,11,-103,92,33,-108,69,17,-63,-75,112,93,-101,-109,39,-113,-47,-35,-35,-51,-65,126,-9,22,2,-63,32,-1,120,-47,69,-108,-123,66,-124,-117,-61,4,-126,1,-18,-68,-19,54,58,59,-37,49,77,-109,116,58,13,100,-21,-44,-89,-15,124,105,-41,18,4,-127,-107,43,87,-110,74,-115,33,74,50,-17,-66,-67,-25,-126,55,94,127,-67,46,53,-98,-58,48,13,50,-70,-123,-86,-86,-40,-106,-123,-125,-120,-32,58,8,-110,-124,-21,10,-72,56,8,72,8,-126,0,-114,-61,-44,-87,83,-119,-58,19,-124,67,-123,-52,-100,57,19,85,85,-103,54,109,26,69,69,-123,28,-23,104,67,-110,36,-4,126,63,-111,72,100,66,33,-99,-128,-25,-53,18,-87,-84,-84,116,111,-65,-3,118,78,-98,60,-55,-64,-64,0,-119,68,-126,84,42,-123,-82,-21,-24,-90,65,38,-109,-63,-74,44,44,-37,-58,48,-116,-20,-28,46,-128,-120,32,8,-88,-86,-126,99,-103,60,-16,-64,3,68,34,17,-74,-65,-77,-121,121,51,103,82,49,-87,-116,-62,-62,66,-46,-23,52,-86,-86,-30,-13,-7,-16,-5,-3,-8,-3,126,70,71,71,-103,60,121,50,-74,109,83,93,93,61,1,-5,121,19,57,112,-32,64,127,36,18,-87,80,85,21,-57,113,38,-104,109,-37,-40,57,-32,-70,-82,99,89,22,-114,-29,96,24,6,0,-114,-29,-112,127,14,96,100,100,-124,-63,-63,65,84,85,-27,-10,-37,111,-9,-98,93,-74,108,25,119,-35,117,23,-109,39,79,38,16,8,-96,105,26,-126,32,32,-53,50,-7,36,50,117,-22,-44,9,-40,-49,-53,-75,-74,111,-33,-18,-106,-108,-108,0,96,-102,-90,7,-36,113,-78,41,-45,113,28,-81,49,52,12,3,-37,-74,-55,119,-70,89,21,-78,109,-121,-21,-70,-76,-75,-75,-31,-70,46,-86,-86,34,-118,34,-77,103,-49,-26,-66,-5,-18,-61,117,93,-4,126,63,37,37,37,20,21,21,33,73,18,-114,-29,16,8,4,-80,44,-117,79,119,-50,-25,75,68,-40,-70,117,-85,83,93,93,-19,-83,-14,-23,10,-100,110,-106,101,77,32,99,89,22,-78,44,19,14,-121,-47,117,-99,93,-69,118,17,12,6,41,47,47,-25,-99,119,-34,-31,-37,-33,-2,54,-118,-94,48,123,-10,108,28,-57,-95,-96,-96,-128,-30,-30,98,-90,78,-99,74,50,-103,-92,-96,-96,0,81,20,61,21,13,-61,-32,-56,-111,35,-25,79,-92,-67,-67,-35,109,105,105,97,-6,-12,-23,30,-127,-68,26,-89,-85,-110,127,-97,7,111,-102,38,-114,-29,32,-118,34,53,53,53,108,-36,-72,17,-65,-33,79,99,99,35,-97,124,-14,9,95,-5,-38,-41,40,47,47,39,-109,-55,112,-8,-16,97,106,106,106,-16,-7,124,-108,-107,-107,17,8,4,24,29,29,-91,-76,-76,20,81,20,105,109,109,101,-2,-4,-7,-60,-29,113,-70,-70,-70,88,-76,104,-47,-7,17,-7,-16,-61,15,93,73,-110,40,41,41,-63,-17,-9,123,-32,108,-37,38,-109,-55,120,123,-116,-68,18,-7,-67,71,-98,-80,-90,105,-52,-99,59,-105,71,30,121,-124,-122,-122,6,26,26,26,16,4,1,-45,48,57,113,-30,4,126,-65,31,85,85,-87,-84,-84,-92,-94,-94,-126,-46,-46,82,-4,126,63,-59,-59,-59,-56,-78,-52,-87,83,-89,-120,-59,98,8,-126,64,107,107,43,-11,-11,-11,92,115,-51,53,103,-51,90,-97,73,100,-1,-2,-3,110,44,22,-29,-91,-105,94,98,-55,-110,37,94,44,-28,87,61,111,-106,101,121,-124,50,-103,12,-74,109,35,8,2,62,-97,-113,89,-77,102,-79,110,-35,58,-106,46,93,-22,-19,77,-6,-6,-6,-48,52,-115,68,34,-127,-49,-25,35,16,8,80,87,87,71,44,22,-13,98,67,-110,36,58,58,58,-68,5,-53,100,50,30,-23,112,56,76,34,-111,-8,-30,68,12,-61,32,24,12,18,-119,68,-48,52,-51,3,-98,-33,48,-91,82,41,50,-103,-116,-25,70,-7,123,0,-102,-90,-79,112,-31,66,30,123,-20,49,-106,46,93,-54,-87,83,-89,24,28,28,68,81,20,2,-127,-128,-25,-122,-39,42,94,64,75,75,11,43,86,-84,-96,-84,-84,-116,-114,-114,14,47,113,-24,-70,78,42,-107,34,-99,78,35,73,18,-102,-90,49,115,-26,76,-58,-57,-57,25,26,26,-102,-128,-9,-84,-107,125,-50,-100,57,-118,109,-37,72,-110,-60,-76,105,-45,-68,-76,-104,79,-85,-70,-82,-109,78,-89,-49,106,-94,40,114,-23,-91,-105,-78,110,-35,58,-26,-49,-97,-49,-31,-61,-121,-7,-28,-109,79,80,20,5,-65,-33,-17,-91,-45,-78,-78,50,111,91,123,-45,77,55,81,94,94,78,123,123,-69,-89,66,42,-107,98,108,108,-116,100,50,73,34,-111,32,-109,-55,-80,103,-49,30,-106,47,95,78,56,28,62,3,-13,89,-119,-36,120,-29,-115,-58,51,-49,60,-125,-29,56,20,23,23,-29,-70,-18,4,119,58,61,-75,-26,-91,-49,-9,73,-43,-43,-43,-84,95,-65,-98,-6,-6,122,-38,-38,-38,24,29,29,-27,-47,71,31,-27,-63,7,31,-28,-118,43,-82,96,-54,-108,41,76,-98,60,25,-61,48,88,-78,100,9,-57,-113,31,71,-106,101,-38,-38,-38,-80,44,-53,91,-92,-79,-79,49,18,-119,4,-119,68,-126,-79,-79,49,108,-37,-58,-25,-53,110,-31,-25,-50,-99,123,6,-26,-77,22,-60,123,-18,-71,-57,13,-121,-61,52,52,52,80,94,94,-114,-21,-70,30,-32,60,-24,-45,-81,-13,-121,9,-63,96,-112,-98,-98,30,124,62,31,47,-65,-4,50,-31,112,-104,-82,-82,46,-90,77,-101,-26,-43,-116,7,30,120,0,-61,48,88,-72,112,-95,-41,-86,-17,-40,-79,3,69,81,-68,126,-22,116,69,-46,-23,52,-82,-21,50,109,-38,52,-62,-31,48,39,78,-100,-32,-110,75,46,-95,-82,-82,-18,-36,5,-79,-92,-92,-124,-70,-70,58,-54,-54,-54,16,69,17,-37,-74,-67,123,-7,-67,2,-128,-108,107,-59,-13,-41,62,-51,-57,-92,73,-109,-40,-78,101,11,-41,93,119,29,91,-74,108,-95,-73,-73,-105,29,59,118,112,-39,101,-105,-15,-30,-117,47,34,73,18,-79,88,12,77,-45,-56,100,50,56,-114,-61,-111,35,71,-72,-16,-62,11,49,12,-61,-117,-67,100,50,73,42,-107,-62,-78,44,74,75,75,-15,-7,124,-60,-29,113,-70,-69,-69,25,25,25,57,-73,107,125,-4,-15,-57,86,95,95,31,-119,68,-126,64,32,-128,-94,40,40,-118,-126,36,73,-120,98,-10,-21,-94,40,-94,-86,42,-78,44,-93,105,26,62,-97,15,-97,-49,-57,15,-41,-4,-112,87,94,121,-123,117,-21,-42,-47,-36,-36,-116,40,-118,-52,-99,59,-105,-25,-97,127,-98,-82,-82,46,-17,-71,-68,123,44,93,-70,20,-41,117,-23,-23,-23,97,108,108,-116,120,60,78,50,-103,-12,-36,-54,48,12,74,75,75,-87,-86,-86,98,-63,-126,5,-116,-115,-115,113,-3,-11,-41,-77,120,-15,-30,115,-69,86,58,-99,118,91,91,91,17,69,-111,-110,-110,18,-74,108,-39,-62,-61,15,63,76,40,20,-62,52,77,94,120,-31,5,-81,119,-78,44,11,-37,-74,113,93,-105,-3,-5,-9,-93,40,10,91,-73,110,-11,26,-67,-30,-30,98,68,81,100,-33,-66,125,-4,-18,119,-65,67,81,20,34,-111,8,-77,102,-51,-94,-92,-92,4,-97,-49,-57,-79,99,-57,120,-6,-23,-89,41,40,40,-104,-32,-78,121,37,-90,79,-97,78,73,73,9,-79,88,-116,119,-33,125,-105,107,-81,-67,22,-97,-49,119,70,-81,117,6,-111,-106,-106,22,-73,-72,-72,24,-37,-74,89,-79,98,5,-105,95,126,57,7,15,30,36,26,-115,-14,-58,27,111,120,5,-55,48,12,-94,-47,40,127,-4,-29,31,-111,101,-103,72,36,-62,-122,13,27,24,27,27,-93,-89,-89,-121,13,27,54,16,-117,-59,104,111,111,-89,-78,-78,-110,84,50,69,105,89,41,-43,-43,-43,124,-3,-21,95,-89,-69,-69,-37,-13,-9,95,-4,-30,23,0,19,10,108,40,20,-94,-79,-79,17,77,-45,-40,-67,123,55,0,-65,-6,-43,-81,-40,-67,123,55,-114,-29,112,-63,5,23,124,126,-116,-120,-94,-56,-116,25,51,-104,59,119,46,-43,-43,-43,-20,-35,-69,-105,104,52,-54,-21,-81,-65,78,60,30,-89,-76,-76,-108,-50,-50,78,34,-111,8,-13,-26,-51,-29,-106,91,110,-95,-91,-91,5,-65,-33,-49,-102,53,107,-68,2,-87,-21,58,-114,-29,80,94,94,78,111,111,47,-115,-115,-115,20,21,21,113,-30,-60,9,4,65,-32,-29,-113,63,102,-35,-70,117,20,21,21,-111,76,38,61,117,29,-57,33,24,12,82,83,83,67,56,28,-26,-107,87,94,97,96,96,-128,-54,-54,74,78,-100,56,65,38,-109,65,81,-50,-36,-19,-98,65,36,-107,74,113,-16,-32,65,110,-69,-19,54,94,123,-19,53,-58,-57,-57,41,42,42,98,-59,-118,21,36,-109,73,10,11,11,9,-123,66,-24,-70,78,87,87,23,-82,-21,-46,-44,-44,68,103,103,39,-82,-21,-110,78,-89,73,38,-109,100,50,25,116,93,-89,-74,-74,-106,-102,-102,26,20,69,-95,-96,-96,-128,-50,-50,78,66,-95,16,29,29,29,44,88,-80,-128,-109,39,79,-30,56,14,-29,-29,-29,-120,-94,72,113,113,49,51,102,-52,-96,-74,-74,-106,-51,-101,55,115,-20,-40,49,70,70,70,-40,-68,121,51,-82,-21,114,-20,-40,49,52,77,59,55,-111,-47,-47,81,-118,-118,-118,88,-77,102,13,-63,96,-112,-33,-1,-2,-9,-68,-9,-34,123,-76,-73,-73,51,56,56,72,52,26,-11,-4,88,-41,117,76,-45,-60,-25,-13,-15,-22,-85,-81,-78,124,-7,114,4,65,-96,-72,-72,56,-101,-59,114,73,-64,-17,-9,-77,103,-49,30,36,73,2,-96,-79,-79,17,89,-106,25,30,30,70,-41,117,-81,-75,9,-123,66,-44,-42,-42,-46,-44,-44,68,115,115,51,35,35,35,-60,-29,113,-2,-4,-25,63,-109,72,36,16,69,-111,88,44,-58,-83,-73,-34,122,110,34,123,-9,-18,37,18,-119,32,-118,34,-29,-29,-29,44,91,-74,44,-69,37,-51,-71,93,-66,102,60,-7,-28,-109,28,63,126,-100,-35,-69,119,-45,-41,-41,-57,-102,53,107,-72,-6,-22,-85,9,-123,66,-88,-86,-118,-86,-86,-76,-75,-75,121,-124,93,-41,-11,10,90,81,81,17,-102,-90,81,87,87,71,58,-99,-10,-10,42,-75,-75,-75,-24,-70,-50,67,15,61,68,127,127,63,77,77,77,60,-2,-8,-29,-60,-29,113,15,95,36,18,-95,-88,-88,-88,-18,-45,45,-54,25,-63,126,-1,-3,-9,-69,-43,-43,-43,-36,122,-21,-83,19,-70,-52,-4,126,0,-16,62,119,93,-105,-83,91,-73,-78,114,-27,74,54,109,-38,68,125,125,-3,-124,70,50,-33,-38,-92,82,41,84,85,-59,-17,-9,-109,76,38,105,104,104,-32,-87,-89,-98,-30,39,63,-7,9,117,117,117,-36,125,-9,-35,-44,-43,-43,113,-8,-16,97,6,7,7,-119,-57,-29,-20,-35,-69,23,-45,52,25,28,28,-4,-40,113,-100,-1,-43,52,-19,7,-82,-21,82,86,86,-58,-87,83,-89,34,64,-20,116,-36,103,-44,17,-53,-78,-8,-34,-9,-66,-57,91,111,-67,-27,85,-11,-68,26,30,123,65,-16,108,-43,-86,85,-72,-82,-53,13,55,-36,64,95,95,31,-47,104,-108,-47,-47,81,18,-119,4,-55,100,18,93,-41,17,4,-127,-66,-34,62,50,-103,12,-49,62,-5,44,43,87,-82,-92,-71,-71,-103,-57,30,123,-116,-122,-122,6,76,-45,-92,-75,-75,-107,-109,39,79,-14,-83,111,125,-117,125,-5,-10,49,48,48,64,127,127,-1,118,-57,113,122,-127,-117,-14,-13,-27,-108,40,58,-89,107,37,-109,73,92,-41,-27,15,127,-8,-125,-9,-65,69,81,81,17,-82,-21,-110,76,38,73,-89,-45,-124,-61,97,-49,101,-14,67,81,20,58,59,59,9,6,-125,-98,107,13,13,13,113,-17,-67,-9,-94,-86,42,-101,54,109,34,-109,-55,-80,125,-5,118,22,44,88,-128,-94,40,-68,-3,-10,-37,4,2,1,116,93,-89,-81,-81,-113,67,-121,14,-79,99,-57,14,-6,-5,-5,-57,108,-37,-18,4,-62,-128,13,-24,-70,-82,-65,10,-60,-127,77,-64,-55,115,18,-71,-2,-6,-21,121,-4,-15,-57,-71,-8,-30,-117,-67,-3,-13,-116,25,51,88,-65,126,61,111,-67,-11,22,-111,72,-124,-15,-15,113,-54,-53,-53,25,26,26,-14,90,-4,-85,-82,-70,-118,-15,-15,113,-58,-58,-58,104,110,110,38,16,8,80,88,88,-120,47,-32,-29,-62,-86,11,-67,-61,8,81,20,49,12,-125,39,-98,120,-126,-23,-45,-89,-13,-26,-101,111,114,-47,69,23,-79,109,-37,54,-110,-55,36,-90,105,30,38,-21,-14,26,96,0,105,96,12,24,7,-42,3,123,115,-28,62,-97,-56,-108,41,83,-72,-7,-26,-101,-103,50,101,10,55,-34,120,35,119,-34,121,39,-5,-10,-19,-93,-87,-87,-119,121,-13,-26,-95,105,26,-94,40,50,109,-22,52,-90,-41,77,71,16,4,-10,-17,-33,-49,-24,-24,40,-78,44,-13,-46,75,47,33,8,2,-21,-41,-81,103,-11,-22,-43,-120,-94,-56,-127,3,7,72,38,-109,-34,-63,-61,-84,89,-77,-24,-18,-18,-90,-86,-86,-118,84,42,-59,115,-49,61,-121,-29,56,-106,101,89,71,114,-104,28,32,-109,35,-112,4,70,-127,-121,-127,30,-32,-84,-89,15,103,4,123,40,20,114,118,-19,-38,37,12,12,12,-80,124,-7,114,47,-73,15,15,15,19,12,6,41,44,44,100,-39,-78,101,104,-102,-26,-75,39,-128,-89,-34,11,47,-68,-128,44,-53,56,-114,-61,-3,-9,-33,-49,-38,-75,107,-111,36,-119,-121,31,126,24,89,-106,89,-67,122,53,-110,36,-79,101,-53,22,-98,120,-30,-119,124,-128,-73,-99,-122,-59,-54,-87,-112,-52,-87,112,2,120,48,-25,86,-6,-39,-44,56,-85,34,-119,68,66,92,-78,100,-79,-5,-34,123,123,-39,-68,121,51,-37,-73,111,-25,-48,-95,67,-34,113,101,60,30,-25,-59,23,95,68,20,69,116,93,71,81,20,47,67,-83,94,-67,26,-53,-78,-112,36,9,69,81,-72,-25,-98,123,104,108,108,-28,-41,-65,-2,53,85,85,85,108,-37,-74,13,-41,117,-71,-14,-54,43,17,69,-111,-22,-22,106,14,28,56,-112,-97,-38,-50,-111,72,-99,-90,-60,-5,-64,51,-71,-49,-52,-100,82,103,29,103,109,-29,-121,-122,-122,-123,-90,-90,38,119,-7,-14,-27,-20,-40,-79,-125,-3,-5,-9,-13,-89,63,-3,-119,-82,-82,46,-114,31,63,-50,-32,-32,32,-87,84,-118,-15,-15,113,6,6,6,-48,52,-115,-19,-37,-73,51,105,-46,36,118,-18,-36,-119,-33,-17,7,96,-50,-100,57,-52,-102,53,-117,-114,-114,14,118,-17,-34,-51,-47,-93,71,-67,122,82,91,91,-53,-30,-59,-117,-39,-76,105,83,103,-114,-128,-111,3,-97,-52,1,-1,111,-32,-51,-36,-75,69,-18,-100,-14,-77,-58,-25,-99,52,74,126,-65,-33,-78,44,-117,96,48,72,69,69,5,-123,-123,-123,68,-93,81,-26,-49,-97,-49,-86,85,-85,-88,-81,-81,-57,-17,-9,-29,56,14,111,-68,-15,6,-15,120,-100,-70,-70,58,-62,-31,48,27,55,110,-28,-32,-63,-125,116,119,119,123,-121,22,-126,32,96,-37,54,107,-41,-82,69,85,85,62,-8,-32,3,-74,110,-35,-6,1,-39,120,72,-99,70,-92,25,56,66,-42,-107,-100,115,-111,56,23,17,31,112,35,-16,3,81,20,43,29,-57,25,-56,-3,-80,40,73,82,-127,36,73,83,93,-41,-107,32,27,31,-94,40,78,40,-96,-126,32,-32,-70,-82,87,111,-14,67,20,69,42,42,42,-88,-86,-86,-30,71,63,-6,17,-33,-4,-26,55,-33,33,27,19,41,96,8,-72,47,-9,106,-14,25,-15,112,62,68,38,3,-53,-127,38,96,42,-39,124,-18,3,36,-78,69,84,-56,-67,-26,-85,-92,112,-102,-99,49,-121,-33,-17,-81,-49,39,6,-97,-49,-121,-86,-86,-68,-1,-2,-5,44,92,-72,-112,-98,-98,-98,-41,115,68,-38,-127,71,-55,6,-72,-63,23,80,-31,92,68,10,-127,41,64,53,80,-107,35,82,-98,35,19,0,84,-78,-79,37,-27,76,56,-19,53,79,50,-1,-69,-34,61,69,81,46,-50,31,68,91,-106,69,89,89,89,-66,105,124,25,-40,6,108,-55,17,-78,-49,-105,4,-71,73,-50,54,-14,-39,35,5,36,114,54,-98,-77,124,48,-22,100,125,59,-13,25,-41,122,14,88,6,48,28,-57,25,-112,36,-23,2,-57,113,16,4,1,-57,113,72,38,-109,47,0,79,-27,-120,124,102,106,-3,34,-29,-77,92,75,36,-69,-14,126,-78,10,-123,-56,-10,55,97,-96,56,-9,62,68,86,-95,0,-39,42,-84,-27,-98,81,-104,-24,118,-112,93,97,25,-72,16,-104,36,8,-126,-22,-70,-18,110,-32,94,-32,24,-25,72,-83,127,9,-111,79,127,71,-50,-127,-12,-27,-52,127,26,-119,96,-18,125,48,119,79,-29,-1,93,-51,33,-69,-54,6,89,53,-121,-127,-66,-100,-23,-89,-35,63,111,87,-6,50,68,-50,-10,76,-34,36,-78,10,72,100,-55,-54,100,-107,112,115,102,-25,-52,36,-21,-82,-7,-10,-30,11,-91,-44,-13,25,-1,7,102,7,124,-12,-77,-90,-113,-61,0,0,0,0,73,69,78,68,-82,66,96,-126";
    return (p1);
}

// int main()
// {
   

//     std::ifstream f("cardata.json");
//     json data = json::parse(f);

    
//     Data d;
    
//     CarStatusParse objCarStatusParse;
//     objCarStatusParse = setCarData(data);
//     struct stutCarValue p1;
  
//     struct stutCarValue p2;
//     p2 = getCarData(objCarStatusParse, p1);
//     //cout << "in main func" << endl;
    
//      const json j1 { p2 };       
//         // Get JSON object from Person
//     const auto s1 = j1.dump(4);         // Get JSON string with indentation (4 spaces)
//     std::cout << s1 << '\n';
//     // std::string abc =  "trunk : "+p2.trunk+" "+ "level : " +p2.level;
//     // cout << abc <<endl;
//     // cout << "bat=" << "trunk : "  <<p2.trunk+" "+ "level : " <<p2.level+" "+ "speed : "<< p2.speed+ " "+"current_temp
//     // : "<<p2.current_temp+" "+"ac : "<<p2.ac+" "+"sun_roof_stste : "<< p2.sun_roof_state + " "+"engne : "<<p2.engine+"
//     // "+"hazard : "<< p2.hazard+" "+"min_temp : "<<p2.min_temp+ " "+ "max_temp : "<<p2.max_temp+ " "+"bonet :
//     // "<<p2.bonet+ " "+"child_lock : "<< p2.child_lock + " "+ "door_fronr_left : "<<p2.door_front_left + " "
//     // +"door_front_right : "<< p2.door_front_right+ " "+"door_rear_left : "<< p2.door_rear_left+ " "+"door_rear_right :
//     // "<< p2.door_rear_right + " "+"window_front_left : "<< p2.WFleft + " "+"window_front_right : "<< p2.WFright + "
//     // "+"window_rear_left : "<< p2.WRleft + " "+"window_rear_right : "<< p2.WRright + " "+"light"<< p2.lights + "
//     // "+"side_mirror_left : "<< p2.SMleft + " "+"side_mirror_right : "<< p2.SMrighi + " "+"sum_volt : "<< p2.sum_volt +
//     // " "+"current : "<<p2.current+ " "+"temperature : "<<p2.temperature+ " "+"voltage : "<< p2.voltage+ " "+"mode :
//     // "<<p2.mode+ " "+"soc : "<<p2.soc+ " "+"soh : "<< p2.soh+ " "+"defrost_front : "<<p2.defrost_front+ " "
//     // +"defrost_rear : "<< p2.defrost_rear+ " "+"air_circulation : "<<p2.air_circulation+ " "+"ac_state :
//     // "<<p2.HFac_state+ " "+"ac_vent_flow : "<<p2.HFac_vent_flow+ " "+"temperature : "<<p2.HFtemperature+ " "+"ac_state
//     // : "<<p2.HRac_state+ " "+"ac_vent_flow : "<< p2.HRac_vent_flow+ " "+"temperature : "<< p2.HRtemperature+ "
//     // "+"current_location_long : "<< p2.current_location_long+ " "+"current_location_lat : "<<p2.current_location_lat+
//     // " "+"d_long : "<<p2.d_long+ " "+"d_lat : "<<p2.d_lat+ " "+"s_long : "<<p2.s_long+ " "+"s_lat : "<<p2.s_lat+ "
//     // "+"g_long : "<<p2.g_long+ " "+"g_lat : "<< p2.g_lat+ " "+"radius : "<<p2.radius << endl;

//     return 0;
// }
