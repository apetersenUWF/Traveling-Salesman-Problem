CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o graph.o rand.o brute-force.o menu.o evolution.o stopwatch.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : menu.o
graph.o: graph.hpp
rand.o: rand.hpp
brute-force.o: brute-force.hpp graph.hpp stopwatch.hpp
menu.o: menu.hpp graph.hpp brute-force.hpp evolution.hpp
evolution.o: evolution.hpp graph.hpp stopwatch.hpp
stopwatch.o: stopwatch.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)