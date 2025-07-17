# Makefile for SystemC D Flip-Flop Simulation

# Path to SystemC installation
SYSTEMC_HOME = /home/vicky/scprojects/demux

# Compiler and flags
CXX = g++
CXXFLAGS = -I. -I$(SYSTEMC_HOME)/include -Wall -g
LDFLAGS = -L$(SYSTEMC_HOME)/lib-linux64 -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64 -lsystemc -lm

# Target and sources
TARGET = main
SRCS = dmux.cpp

# Default build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up build artifacts
clean:
	rm -f $(TARGET) *.o *.vcd



