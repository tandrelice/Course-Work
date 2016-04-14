#  CS246.  February 2013.  Make file for testunion program.
#     Run this using gmake (not make)
#     On Linux, the gmake command is spelled as make

CXX = g++
CXXFLAGS = -g -Wall 
OBJECTS = newsetint.o testunion.o

EXEC = testunion

all : ${EXEC}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@

setint.o : newsetint.h

testunion.o : newsetint.h

clean :
	rm -f ${EXEC} ${OBJECTS}
