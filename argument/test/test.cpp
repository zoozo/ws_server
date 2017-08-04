#include "../src/argument.hpp"

#include <iostream>
using namespace zoozo;
using namespace std;
using namespace boost;

int main(){
    cout<<"*****start*****"<<endl;
    argument_map arg_map;
    arg_map.insert(argument_map::value_type("name1", "a"));
    arg_map.insert(argument_map::value_type("name1", "b"));
    arg_map.insert(argument_map::value_type("name2", 3));
    arg_map.insert(argument_map::value_type("name2", 4));

    argument args(arg_map);
    cout<<"count:"<<args.get_count("name1")<<endl;
    cout<<"name2:"<<args.get<int>("name2")<<endl;
    cout<<"name2:"<<args.get<std::string>("name1")<<endl;
    vector<string> data;
    int count = args.get("name1", data);
    cout<<"count:"<<count<<endl;
    cout<<data[0]<<endl;

    
}

