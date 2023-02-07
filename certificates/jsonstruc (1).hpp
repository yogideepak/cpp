#include "json.hpp"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>
#include<fstream>
#include<iostream>
#include<string>
#include<jsoncpp/json/value.h>
#include<jsoncpp/json/json.h>
#include<string>
#include"sqlite3.h"
#include<stdlib.h>
using namespace std;

using json = nlohmann::json;

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

namespace ns {
    // a simple struct to model a person
    struct stutCarValue {
        std::string vin;
        std::string fuel;
        std::string speed;
        std::string level;
        std::string door;
        std::string trunk;
        std::string AC;
        std::string mintemp;
        std::string maxtemp;
    };

    void to_json(json& j, const stutCarValue& p) {
        j = json{{"vin", p.vin}, {"fuel", p.fuel}, {"speed", p.speed}, {"level", p.level},{"door",p.door},{"trunk",p.trunk},{"AC",p.AC},{"min temp",p.mintemp},{"max temp",p.maxtemp}};
    }

    void from_json(const json& j, stutCarValue& p) {
        j.at("vin").get_to(p.vin);
        j.at("fuel").get_to(p.fuel);
        j.at("speed").get_to(p.speed);
        j.at("level").get_to(p.level);
        j.at("door").get_to(p.door);
        j.at("trunk").get_to(p.trunk);
        j.at("AC").get_to(p.AC);
        j.at("min temp").get_to(p.mintemp);
        j.at("max temp").get_to(p.maxtemp);

    }
}