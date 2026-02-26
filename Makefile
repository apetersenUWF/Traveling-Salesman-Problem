CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o menu.o evolution.o brute-force.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : menu.hpp
menu.o : menu.hpp
evolution.o: evolution.hpp
brute-force.o: brute-force.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)