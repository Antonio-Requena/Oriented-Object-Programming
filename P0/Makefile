DIR = ../Tests-auto/
CXX = g++
STD = c++11
CXXFLAGS = -std=${STD} -g -pedantic -Wall
CPPFLAGS = -DP0 -I../Tests-auto -I.
LDFLAGS = -I$(DIR)
VPATH = ../Tests-auto:.
OBJS = test-P0-consola.o fecha.o cadena.o 
EXE = test-P0-auto test-fechacadena-consola test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o

all: test-P0-consola test-P0-auto


test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test-P0-consola.o: test-fechacadena-consola.cpp fecha.hpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

fecha.o: fecha.cpp fecha.hpp 
	$(CXX) -c $(CXXFLAGS) $< -o $@

cadena.o: cadena.cpp cadena.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
  test-auto.o cadena.o fecha.o
	$(CXX) -o $@ $^

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
      test-auto.hpp fecha.hpp cadena.hpp
clean:
	$(RM)	$(OBJS) $(EXE)
