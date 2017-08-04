UP_CC = g++
LIB = -lboost_log -L../../../lib -lgeneric_module
INC = 
CPPS = minus.cpp \
 
main:
	${UP_CC} minus.cpp -m64 -Wall  -fpic -shared -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK ${INC} ${LIB} -g -o ../../../lib/libminus.so
	${UP_CC} plus.cpp -m64 -Wall  -fpic -shared -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK ${INC} ${LIB} -g -o ../../../lib/libplus.so
	${UP_CC} chat.cpp -m64 -Wall  -fpic -shared -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK ${INC} ${LIB} -g -o ../../../lib/libchat.so
  
clean:
	@rm -rf *.o *.so
