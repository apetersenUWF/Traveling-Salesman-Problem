#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP
#include "graph.hpp"
struct EvolutionResults{
    int tourLength;
    int toursPerGeneration;
    int generations;
    float mutationRate;
    float bestTour;
    float timeToSolve;
};
class Evolution{
    Graph* graph;
    int tourLength;
    int toursPerGeneration;
    int generations;
    float mutationRate;
    int* tour;
    int* elite;
    float bestTour;
    public:
    Evolution();
    Evolution(Graph* graph, int tourLength, int toursPerGeneration, int generations, float mutationRate);
    ~Evolution();
    EvolutionResults run();
};
#endif