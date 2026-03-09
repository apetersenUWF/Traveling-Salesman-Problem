#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP
#include "graph.hpp"
const int ELITE_OFFSPRING_MAX = 8;
struct EvolutionResults{
    int tourLength;//number of cities in each tour, not including start and end point
    int toursPerGeneration;//tours to try in each generation
    int generations;//generations to run
    float mutationRate;//percent chance of a mutation
    float bestTour;//shortest tour distance found so far
    double timeToSolve;//total number of tours checked, should finish as gens*toursPerGen
    float bfOptimal;//optimal solution found for brute force of the same tourlength
    double bfOptimalTime;//time brute force took to find the optimal soln
    float percentOptimal;
    double percentOptimalTime;
};
class Evolution{
    Graph* graph;
    int tourLength;
    int toursPerGeneration;
    int generations;
    float mutationRate;
    int* tour;//current tour being checked, modified in place using perm1()
    int* elite;//best touyr from the current generation
    float bestTour;
    void mutate(int* tour);//takes a tour and has a chance of mutating based on mutationRate
    void processTour(int* tour);//updates the elite, bestTour, toursSearched variables
    public:
    Evolution();
    Evolution(Graph* graph, int tourLength, int toursPerGeneration, int generations, float mutationRate);
    ~Evolution();
    EvolutionResults run();
};
#endif