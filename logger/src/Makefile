UP_CC = g++
LIB =  -lpthread -lboost_log 
INC = 
CPPS = logger.cpp \
 
main:
	${UP_CC} ${CPPS} -m64 -Wall  -fpic -shared -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK  ${INC} ${LIB} -g -o ../../lib/liblogger.so
  
clean:
	@rm -rf *.o *.so
