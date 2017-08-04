//#include "../module/generic_module.h"                                                       
#include "../src/plugin.h"
#include <boost/shared_ptr.hpp>
#include <iostream>                                                          

using namespace zoozo;
using namespace std;
                                                                             
int main() {                                                                 

    plugin plin("../../conf/modules.json");
//    create_t *t = plin._load_library("../lib/libtriangle.so");
    //boost::shared_ptr<create_t> t = plin._load_library("../lib/libsquare.so");
    boost::shared_ptr<generic_module> p3 = plin.create("plus");
    boost::shared_ptr<generic_module> p5 = plin.create("chat");
    std::multimap<std::string, std::string> input;
    input.insert(std::multimap<std::string, std::string>::value_type("message", "hello world"));
    input.insert(std::multimap<std::string, std::string>::value_type("name", "zzz"));
    input.insert(std::multimap<std::string, std::string>::value_type("a", "5"));
    input.insert(std::multimap<std::string, std::string>::value_type("b", "5.3"));
    string module1 = "chat";
    string module2 = "plus";
    map<string,string> args;
    string output;
    if(!p3->validate("../../conf/validate.json",module2, input)){
        cout<<p3->get_validate_error()<<endl;
    }
    p3->run(output);                    
    cout<<output<<endl;
    if(!p5->validate("../../conf/validate.json", module1, input)){
        cout<<p5->get_validate_error()<<endl;
    }
    p5->run(output);                    
    cout<<output<<endl;


    return 0;
} 
