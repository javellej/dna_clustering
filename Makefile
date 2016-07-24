CXX=/usr/bin/g++
CPPFLAGS=-std=c++0x -O2
SRC=src/main.cpp src/Tools.cpp
INC=-Iinc/

all: main

main: $(SRC)
	$(CXX) $(CPPFLAGS) -o deskGen $(SRC) $(INC)

clean:
	rm -f deskGen
