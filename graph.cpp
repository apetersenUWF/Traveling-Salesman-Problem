/***************************************************************
  Ayden Petersen
  graph.cpp
  Project 3

  This file contains the necessary logic to load a complete graph
  for the traveling salesman problem from a file and store it as a 1d
  adjacency matrix (adjMatrix). It also contains the necessary methods
  to calculate the total distance of a tour given a series of nodes 
  (getTourDistance()).
***************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include "graph.hpp"

  Graph::Graph() {
    nodeCount = 0;
  }

  Graph::Graph(const std::string &filename) {
    std::ifstream inFS;
    inFS.open(filename);
    if (inFS.is_open()) {
      nodeCount = DEFAULT_NODE_COUNT;
      adjMatrix.resize(DEFAULT_NODE_COUNT*DEFAULT_NODE_COUNT);
      for (unsigned int i = 0; i < DEFAULT_NODE_COUNT; i++) {
        for (unsigned int j = 0; j < DEFAULT_NODE_COUNT; j++) {
          if (i != j) {//cities wont connect to themselves in the graph
            std::string line;
            getline(inFS, line);
            float x = std::stof(line);
            adjMatrix[(i*DEFAULT_NODE_COUNT) + j] = x;//map to 1d vector
          }
          else adjMatrix[(i*DEFAULT_NODE_COUNT) + j] = 0;//referencing a city to itself, distance is 0, not included in the file
        }
      }
      inFS.close();
    }
  }

  float Graph::at(const unsigned int i, const unsigned int j) const {//returns the value of arrray[i][j] without boundary checks for speed{}
    return adjMatrix[(i*DEFAULT_NODE_COUNT) + j];
  }

  int Graph::size() {return nodeCount;}//returns the nodeCount

  void Graph::print() const {
    printf("%-7s", " ");
    for (unsigned int j = 0; j < DEFAULT_NODE_COUNT; j++) {
      printf("%-7d", j);
    }
    printf("\n");
    for (unsigned int i = 0; i < DEFAULT_NODE_COUNT; i++) {
      printf("%-7d", i);
      for (unsigned int j = 0; j < DEFAULT_NODE_COUNT; j++) {
        float x = adjMatrix[(i*DEFAULT_NODE_COUNT) + j];
        std::cout << std::setprecision(4) << std::setw(5) << std::left << x << "  ";
      }
      printf("\n");
    }
  }

  float Graph::getTourDistance(int* tour, int tourSize) const {//finds the total distance of a tour
    float distance = 0.0;
    int currentCity = START_END_POINT;//initialize start point
    for (int i = 0; i < tourSize; i++){//sum the distance to each of the next cities on the tour
      distance += at(currentCity, tour[i]);
      currentCity = tour[i];//update current city
    }
    distance += at(currentCity, START_END_POINT);//add the distance from the last city of the tour back to the starting point
    return distance;
  }