#include <iostream>
#include "graph.hpp"
#include "permutation.hpp"
#include "brute-force.hpp"
using namespace std;
int main() {
  Graph* graph = new Graph(DEFAULT_FILE);
  BruteForceResults x[13];
  int j = 0;
  for (int i = 1; i <= 13; i++) {
    Solver* y = new Solver(graph, i);
    x[j] = y->run();
    j++;
    delete y;
  }
  for (int i = 0; i < 13; i++) {
    cout << "----------------------------" << endl;
    cout << "Test " << i << endl;
    cout << x[i].tourLength << endl;
    cout << x[i].bestTour << endl;
    cout << x[i].timeToSolve << endl;
  }
  return 0;
}