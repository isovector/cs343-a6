CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = bank.o bottlingplant.o config.o nameserver.o parent.o printer.o student.o truck.o vendingmachine.o watcard.o watcard.office.o  			# optional build of given program
EXECS = soda

DEPENDS = ${OBJECTS:.o=.d}

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables
wordcount: ${EXECS}             # build soda

${EXECS} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC0} ${EXEC00} ${EXECS}
