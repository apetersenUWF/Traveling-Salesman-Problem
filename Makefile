CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = main.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o : 

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)