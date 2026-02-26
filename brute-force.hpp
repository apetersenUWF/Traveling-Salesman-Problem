#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP
#include "graph.hpp"
class Solver{
  int tourLength;
  int* tour;
  float bestTour;
  Graph* graph;
  public:
  Solver();
  Solver(Graph* graph, int tourLength);
  ~Solver();
  float run();
};
#endif