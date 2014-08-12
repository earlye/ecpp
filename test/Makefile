export
WORKSPACE?=$(shell pwd)/..
PWD=$(shell pwd)
ECPP=$(WORKSPACE)
BOOST?=/opt/local/include

ifeq ($(TARGET),mingw-64)
CXX=x86_64-w64-mingw32-g++
endif

CXXFLAGS=-I$(ECPP)
CXXFLAGS+=-I$(BOOST)
CXXFLAGS+=-I$(PWD)
CXXFLAGS+=-g

TEST_SOURCES=$(shell find . -name "*.cpp")
ECPP_SOURCES=$(shell find $(ECPP)/src -name "*.cpp")

SOURCES=$(TEST_SOURCES) $(ECPP_SOURCES)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

all : test.exe

test : test.exe
	./test.exe

test.exe : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

clean :
	rm -f $(OBJECTS)
	rm -f test.exe

.PHONY : emacs
emacs : 
	emacs .

##
# Compile C++ code into .o format.  At the same time, generate a dependency file (%.d), which is just a gnu makefile 
# that says the .o file depends not only on the .c file, but on all the crap included by the .c file as well.                                                                                          
%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MM -o $*.d.tmp $<
#       Workaround arguable bug in gcc -MM mode, where it doesn't include the folder in the .o target.
	sed "s|.*:|$*.o:|g" < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	rm $*.d.tmp
#       Actually compile now.
	$(CXX) $(CXXFLAGS) -c -o $@ $<
#
##

buildEnvironment.hpp :
	touch $@

