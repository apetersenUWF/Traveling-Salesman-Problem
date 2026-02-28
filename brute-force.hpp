#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP
#include "graph.hpp"
struct BruteForceResults{
  int toursToSolve;
  int tourLength;
  float bestTour;
  double timeToSolve;
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