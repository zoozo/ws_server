#include "../src/validation.h"
#include "../../argument/src/argument.hpp"

#include <iostream>
using namespace zoozo;
using namespace std;
using namespace boost;

int main(){
    cout<<"*****start*****"<<endl;
    //argument_map arg_map;
    argument args;

    string conf = "../../ws_server/conf/validate.json";

    validation v(conf);
    std::multimap<std::string, std::string> input;
    input.insert(std::multimap<std::string, std::string>::value_type("a", "1.3"));
    input.insert(std::multimap<std::string, std::string>::value_type("b", "2"));
    input.insert(std::multimap<std::string, std::string>::value_type("triangle2", "5"));
    input.insert(std::multimap<std::string, std::string>::value_type("triangle3", "5.3"));
    input.insert(std::multimap<std::string, std::string>::value_type("triangle4", "5.3"));
    string module = "plus";
    if(!v.validate(module, input, args)){
        cout<<v.get_error_message()<<endl;
    }
    else{
        cout<<args.get<double>("a")<<endl;
    }


    
}

