CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o graph.o permutation.o brute-force.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : graph.hpp
graph.o: graph.hpp
permutation.o: permutation.hpp
brute-force.o: brute-force.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)