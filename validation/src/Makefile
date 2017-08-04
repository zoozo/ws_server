UP_CC = g++
LIB = 
INC = 
CPPS = validation.cpp \
 
main:
	${UP_CC} ${CPPS} -m64 -Wall  -fpic -shared -O2 -std=gnu++0x  ${INC} ${LIB} -g -o ../../lib/libvalidation.so
  
clean:
	@rm -rf *.o *.so
