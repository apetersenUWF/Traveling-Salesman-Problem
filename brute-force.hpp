#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP
#include "graph.hpp"
struct BruteForceResults{
  int tourLength;
  float bestTour;
  float timeToSolve;
};
class Solver{
  int tourLength;
  int* tour;
  float bestTour;
  Graph* graph;
  public:
  Solver();
  Solver(Graph* graph, int tourLength);
  ~Solver();
  BruteForceResults run();
};
#endif