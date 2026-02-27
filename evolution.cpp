/***************************************************************
  Ayden Petersen
  evolution.cpp
  Project 3

  This file contains the necessary logic to run an evolutionary algorithm
  to solve the traveling salesman problem. It takes a complete graph and
  parameters for the algorithm as arguments, then systematically creates
  random tours and mutates them for a number of generations, keeping track
  of the shortest distance found as well as the order of one elite tour to carry
  on to the next generation. It will return a packet, EvolutionResults, that
  contains the parameters used as well as the results.
***************************************************************/
#include "evolution.hpp"
#include "stopwatch.hpp"
    Evolution::Evolution() {
        graph = nullptr;
        tourLength = 0;
        toursPerGeneration = 0;
        generations = 0;
        mutationRate = 0;
        tour = nullptr;
        elite = nullptr;
        bestTour = 0;
    }
    Evolution::Evolution(Graph* graph, int tourLength, int toursPerGeneration, int generations, float mutationRate) {
        this->graph = graph;
        this->tourLength = tourLength;
        this->toursPerGeneration = toursPerGeneration;
        this->generations = generations;
        this->mutationRate = mutationRate;
        tour = new int[tourLength];
        elite = new int[tourLength];
        int i = 0;
        for (int j = 0; j <= tourLength; j++) {
            if (j != START_END_POINT) {
                tour[i] = j;
                elite[i] = j;
                i++;
            }
        }
        bestTour = graph->getTourDistance(tour, tourLength);
    }
    Evolution::~Evolution() {
        delete [] tour;
        delete [] elite;
    }
    EvolutionResults Evolution::run() {
        //do this
    }