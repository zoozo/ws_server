UP_CC = g++
LIB = -lboost_system -lssl -lcrypto -lboost_log -L../../lib -lwsserver -lplugin -llogger
INC = -I ~/git/websocketpp
CPPS = ws_server_d.cpp \

main:
	${UP_CC} ${CPPS} -Wall -O2 -std=c++11 ${INC} ${LIB} -o ws_server

clean:
	@rm -rf *.o *.so
