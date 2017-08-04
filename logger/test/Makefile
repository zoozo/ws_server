UP_CC = g++
LIB = -lpthread -lboost_log -lboost_system -L../../lib -llogger
INC = 
CPPS = test.cpp \

main:
	${UP_CC} ${CPPS} -m64 -Wall -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK  ${INC} ${LIB} -g  -o test

clean:
	@rm -rf *.o *.so
