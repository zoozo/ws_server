#ifndef CHAT_MODULE_H
#define CHAT_MODULE_H
#include "../../generic_module/src/generic_module.h"                                                       
                                                                             
namespace zoozo{
class chat : public generic_module {                                            
public:                                                                      
    chat();
    int run(std::string& output);
                                                                            
    ~chat();
};                                                                           
}
#endif
