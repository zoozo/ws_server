#ifndef PLUS_MODULE_H
#define PLUS_MODULE_H
#include "../../generic_module/src/generic_module.h"                                                       
                                                                             
namespace zoozo{
class plus : public generic_module {                                            
public:                                                                      
    plus();
    int run(std::string& output);
                                                                            
    ~plus();
};                                                                           
}
#endif
