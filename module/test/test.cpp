#include "../src/plus.h"
#include "../../generic_module/src/generic_module.h"
#include <boost/shared_ptr.hpp>

using namespace zoozo;

int main(){
    boost::shared_ptr<generic_module> p1(new plus());

    zoozo::argument args;
    std::string json_conf("../../conf/validate.json");

    std::multimap<std::string, std::string> input;
    input.insert(std::multimap<std::string, std::string>::value_type("a", "1"));
    input.insert(std::multimap<std::string, std::string>::value_type("b", "2"));
    input.insert(std::multimap<std::string, std::string>::value_type("test", "aa"));
    p1->validate(json_conf, "plus", input);
    std::string output;
    p1->run(output);
    std::cout<<"p1:"<<output<<std::endl;
    std::cout<<"finish"<<std::endl;


}
