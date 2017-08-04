UP_CC = g++
LIB = 
INC = 
CPPS = validation.cpp \
 
main:
	${UP_CC} -m64 -Wall  -fpic -shared -O2 -std=gnu++0x  ${INC} ${LIB} -g ${CPPS} -o ../../lib/libvalidation.so
  
clean:
	@rm -rf *.o *.so
