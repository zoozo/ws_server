#include "plus.h"                                                       
#include <boost/lexical_cast.hpp>
                                                                             
namespace zoozo{
plus::plus(){}
int plus::run(std::string& output){
    double a = args.get<double>("a");
    double b = args.get<double>("b");
    double c = a + b;
    output = "{\"message\":\""+ boost::lexical_cast<std::string>(c) +"\",\"name\":\"system\",\"color\":\"F00\"}";
    //output = "1,2,3";
    logger_write(trivial::fatal, output);
    return 0;
}                                                                        

plus::~plus(){}
EXTERN_MODULE(plus);
}
