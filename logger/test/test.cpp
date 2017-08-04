#include "../src/logger.h"

#include <iostream>
using namespace std;
using namespace boost;

int main(){
    zoozo::logger log("test.log");
    log.write(trivial::error, "sss");
    cout<<"*****start*****"<<endl;
    
}

