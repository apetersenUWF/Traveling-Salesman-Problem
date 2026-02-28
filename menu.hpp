#ifndef MENU_HPP
#define MENU_HPP
#include "evolution.hpp"
#include "brute-force.hpp"
#include "graph.hpp"
#include <vector>
class Menu{
    Graph* cities;
    BruteForceResults runBF(int i);
    EvolutionResults runGA();
    void printGAResult(EvolutionResults& result);
    bool createOutputFiles();
    bool saveBFData(std::vector<BruteForceResults>& bfData);
    bool appendGAData(EvolutionResults& gaData);
  public:
    Menu();
    ~Menu();
    void run();
};
#endif