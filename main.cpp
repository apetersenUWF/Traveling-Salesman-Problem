#include <iostream>
#include "graph.hpp"
using namespace std;
int main() {
  Graph* graph = new Graph(DEFAULT_FILE);
  int tour[5] = {2, 8, 18, 9, 11};
  graph->print();
  cout << "--------------------------------------------------" << endl;
  cout << graph->getTourDistance(tour, 5);
  return 0;
}