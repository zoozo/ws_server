UP_CC = g++
LIB = -L/usr/local/lib -ldl
INC = 
CPPS = plugin.cpp \

main:
	${UP_CC} ${CPPS} -m64 -Wall -O2 -fpic -shared -std=gnu++0x  ${INC} ${LIB} -g -o ../../../lib/libplugin.so

clean:
	@rm -rf *.o *.so
