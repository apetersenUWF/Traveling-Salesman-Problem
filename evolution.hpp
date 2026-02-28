#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP
#include "graph.hpp"
const int ELITE_OFFSPRING_MAX = 3;
struct EvolutionResults{
    int tourLength;
    int toursPerGeneration;
    int generations;
    float mutationRate;
    float bestTour;
    double timeToSolve;
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
    void mutate(int* tour);
    void processTour(int* tour);
    public:
    Evolution();
    Evolution(Graph* graph, int tourLength, int toursPerGeneration, int generations, float mutationRate);
    ~Evolution();
    EvolutionResults run();
};
#endif