#include <iostream>
#include "graph.hpp"
#include "permutation.hpp"
#include "brute-force.hpp"
using namespace std;
int main() {
  Graph* graph = new Graph(DEFAULT_FILE);
  Solver* solver = new Solver(graph, 12);
  float x = solver->run();
  cout << x;
  return 0;
}