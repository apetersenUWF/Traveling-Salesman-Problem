#ifndef MENU_HPP
#define MENU_HPP
#include "evolution.hpp"
#include "brute-force.hpp"
#include "graph.hpp"
class Menu{
    Graph* cities;
    BruteForceResults runBF(int i);
    EvolutionResults runGA();
    void printGAResult(EvolutionResults result);
  public:
    Menu();
    ~Menu();
    void run();
};
#endif