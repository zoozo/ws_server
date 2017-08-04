UP_CC = g++
LIB = -L../../../lib -lgeneric_module -lplus -lminus -lvalidation 
INC = 
CPPS = test.cpp \

main:
	${UP_CC} -Wall -O2 -std=gnu++0x -DBOOST_LOG_DYN_LINK ${INC} ${LIB} -g ${CPPS} -o test

clean:
	@rm -rf *.o *.so
