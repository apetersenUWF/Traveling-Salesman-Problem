CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o graph.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : graph.hpp
graph.o: graph.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)