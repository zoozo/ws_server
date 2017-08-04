#include "chat.h"                                                       
namespace zoozo{
chat::chat(){}
int chat::run(std::string& output){
    output = "{\"message\":\""+args.get<std::string>("message")+"\",\"name\":\""+args.get<std::string>("name")+"\",\"color\":\"F00\"}";

    logger_write(trivial::error, output);

    return 0;
}                                                                        
chat::~chat(){ }

EXTERN_MODULE(chat);
}
