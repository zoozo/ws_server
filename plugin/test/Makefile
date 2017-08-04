UP_CC = g++
LIB = -L../../../lib -lplugin -lvalidation -lgeneric_module
INC = 
CPPS = test.cpp \

main:
	${UP_CC} ${CPPS} -m64 -Wall -O2 -std=gnu++0x  ${INC} ${LIB} -g -o test

clean:
	@rm -rf *.o *.so
