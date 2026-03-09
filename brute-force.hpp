#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP
#include "graph.hpp"
struct BruteForceResults{
  int toursToSolve;//number of tours checked for the final solution
  int tourLength;//number of cities in each tour, not including start and end point
  float bestTour;//value from the shortest tour
  double timeToSolve;//time it took to solve in seconds
};
class Solver{
  int tourLength;
  int* tour;//current tour being checked, modified in place using perm1()
  float bestTour;
  Graph* graph;
  public:
  Solver();
  Solver(Graph* graph, int tourLength);
  ~Solver();
  BruteForceResults run();
};
#endif