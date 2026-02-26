#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include <vector>
const unsigned int DEFAULT_NODE_COUNT = 20;
const unsigned int START_END_POINT = 0;
const std::string DEFAULT_FILE = "distances.txt";
class Graph{
  int nodeCount;//holds the total number of nodes
  std::vector<float> adjMatrix;//holds the edge weights for the undirected complete graph, 2d array mapped to 1d
  public:
  Graph();
  Graph(const std::string &filename);
  float at(const unsigned int i, const unsigned int j) const;//returns the value of arrray[i][j] without boundary checks for speed
  int size();//returns the nodeCount
  float getTourDistance(int* tour, int tourSize) const;//returns the total distance of ma tour
  void print() const; //for testing
};
#endif