#include "minus.h"                                                       
#include <boost/lexical_cast.hpp>
                                                                             
namespace zoozo{
int minus::run(std::string& output){
    double a = args.get<double>("a");
    double b = args.get<double>("b");
    double c = a - b;
    output = "{\"message\":\""+ boost::lexical_cast<std::string>(c) +"\",\"name\":\"system\",\"color\":\"F00\"}";
    return 0;
}                                                                        

EXTERN_MODULE(minus);
}
