#CXXFLAGS = -O0 -ggdb -Wall -ansi -fmessage-length=0
CXXFLAGS = -Wall -ansi

tsio: tsio.h tsio.cpp
	c++ $(CXXFLAGS) -o tsio tsio.cpp 

all: tsio

clean:
	rm -f tsio tsio.o
