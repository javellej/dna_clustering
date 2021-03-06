CXX=g++
INC=-Iinc/
CPPFLAGS=-std=c++0x -O2 -Iinc/
OBJ=src/main.o src/Tools.o src/Guide.o src/DataSet.o src/Math.o src/LogReg.o
LIB=-Llib/ -ldlib -lboost_graph

all: deskGen

%.o: %.c
		$(CXX) -c -o $@ $< $(CPPFLAGS)

deskGen: $(OBJ)
		$(CXX) -o $@ $^ $(CPPFLAGS) $(LIB)

clean:
	rm -f deskGen

cleanall:
	rm -f src/*.o
