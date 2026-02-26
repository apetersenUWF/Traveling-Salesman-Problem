#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
class Graph{
  int nodeCount;
  float adjMatrix**;
  public:
  Graph();
  Graph(const std::string &filename);
  float at(const unsigned int i, const unsigned int j) const;
  int size();
};
#endif