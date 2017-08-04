UP_CC = g++
LIB = -L/usr/local/lib -lboost_system -lboost_chrono -lboost_thread -lssl -lcrypto -L../../../lib -lplugin -lgeneric_module  -llogger -lvalidation
INC = -I ~/git/websocketpp
CPPS = server.cpp ws_server.cpp wss_server.cpp ws_util.cpp \
 
main:
	${UP_CC} ${CPPS} -m64 -Wall  -fpic -shared -std=gnu++0x -DBOOST_LOG_DYN_LINK  -g ${INC} ${LIB} -o ../../../lib/libwsserver.so
  
clean:
	@rm -rf *.o *.so
