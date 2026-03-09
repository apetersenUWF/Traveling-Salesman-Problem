/***************************************************************
  Ayden Petersen
  brute-force.cpp
  Project 3

  This file contains the implementations of methods for the Solver
  class, a brute force algorithm that takes a complete graph and the
  length of each tour as arguments, then systematically checks
  each permutaion of possible tours in the run() function until
  all permutations are checked or the program has run for 5 minutes.
  It will return the distance of the tour with the lowest value.
***************************************************************/
#include "brute-force.hpp"
#include "rand.hpp"
#include "stopwatch.hpp"

///////////////////////////////////////////////////////////////////////

  Solver::Solver() {
    tourLength = 0;
    tour = nullptr;
    graph = nullptr;
    bestTour = 0;
  }
  Solver::Solver(Graph* graph, int tourLength) {
    this->tourLength = tourLength;
    tour = new int[tourLength];
    this->graph = graph;
    int i = 0;
    for (int j = 0; j <= tourLength; j++) if (j != START_END_POINT) tour[i++] = j;//generate the first tour, include every city except the starting point
    bestTour = graph->getTourDistance(tour, tourLength);//initialize the first tour as the best tour
  }
  Solver::~Solver() {
    delete [] tour;
  }

///////////////////////////////////////////////////////////////////////

  BruteForceResults Solver::run() {//runs the brute force algorithm for all permutations of tours
    BruteForceResults data;//stores tourLength, timeToSolve, and bestTour
    StopWatch timer;
    data.tourLength = tourLength;
    data.toursToSolve = 0;
    timer.start();//start timing
    while (perm1(tour, tourLength)) {//while we still have permutations to check, permute tour
      data.toursToSolve++;//count tour
      float x = graph->getTourDistance(tour, tourLength);//check the length of this permutation
      if (x < bestTour) bestTour = x;//keep track of lowest tour distance found
    }
    timer.stop();//stop timing
    data.bestTour = bestTour;
    data.timeToSolve = timer.getElapsedTime();
    return data;
  }

