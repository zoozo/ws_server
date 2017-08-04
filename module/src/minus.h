#ifndef MINUS_MODULE_H
#define MINUS_MODULE_H
#include "../../generic_module/src/generic_module.h"                                                       
                                                                             
namespace zoozo{
class minus : public generic_module {                                            
public:                                                                      
    minus(){}
    int run(std::string& output);
    ~minus(){}
};                                                                           
}
#endif
