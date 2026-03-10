#ifndef MENU_HPP
#define MENU_HPP
#include "evolution.hpp"
#include "brute-force.hpp"
#include "graph.hpp"
#include <vector>
class Menu{
    Graph* cities;//holds the adjacency matrix
    BruteForceResults runBF(int i);//run the brute force for tourLength i
    EvolutionResults runGA();//gets parameters from the user and runs the genetic algorithm
    void printGAResult(EvolutionResults& result);//prints the results from the ga after each run
    bool createGAOutputFile();
    bool createBFOutputFile();
    bool saveBFData(std::vector<BruteForceResults>& bfData);
    std::vector<BruteForceResults> loadBFData();
    bool appendGAData(EvolutionResults& gaData, std::vector<BruteForceResults>& bfData);//appends new ga results to the end of the genetic-algorithm-results.csv file
  public:
    Menu();
    ~Menu();
    void run();
    EvolutionResults runRandomGA();
};
#endif