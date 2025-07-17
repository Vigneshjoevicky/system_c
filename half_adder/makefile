# Variables
CXX = g++
CXXFLAGS = -I. -I$(SYSTEMC_HOME)/include
LDFLAGS = -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc -lm -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64

# Targets and Rules
main: half_adder.cpp
	$(CXX) $(CXXFLAGS) -o main half_adder.cpp $(LDFLAGS)

clean:
	rm -f main
