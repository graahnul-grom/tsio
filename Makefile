CXXFLAGS = -O0 -ggdb -Wall -ansi
# CXXFLAGS = -Wall -ansi

test_tsio: tsio.h test.cpp
	c++ $(CXXFLAGS) -o test_tsio test.cpp

all: tsio

clean:
	rm -f test_tsio

