#include "brute-force.hpp"
#include "permutation.hpp"
  Solver::Solver() {
    tourLength = 0;
    tour = nullptr;
    graph = nullptr;
    bestTour = 0
  }
  Solver::Solver(Graph* graph, int tourLength) {
    this->tourLength = tourLength;
    tour = new int[tourLength];
    this->graph = graph;
    int i = 0;
    for (int j = 0; j <= tourLength; j++) if (j != START_END_POINT) tour[i++] = j;
    bestTour = graph->getTourDistance(tour, tourLength);
  }
  Solver::~Solver() {
    delete [] tour;
    delete graph;
  }
  float Solver::run() {
    while (perm1(tour, tourLength)) {
    float x = graph->getTourDistance(tour, tourLength);
    if (x < bestTour) bestTour = x;
    }
    return bestTour;
  }