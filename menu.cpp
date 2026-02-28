/***************************************************************
  Ayden Petersen
  menu.cpp
  Project 3

  This file contains the necessary logic to interact with the user
  as to run the brute force and evolutionary solutions to the traveling
  salesman problem. It runs the brute force algorithm for 10-13 cities, then prompts
  the user for parameters to run the evolutionary algorithm until the user
  terminates the program. It will print the results of each run as well as 
  save all the results to an excel file titled "results.csv" for later analysis.
***************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include "menu.hpp"

    Menu::Menu() {
        cities = new Graph(DEFAULT_FILE);
    }
    Menu::~Menu() {
        delete cities;
    }
    EvolutionResults Menu::runGA() {
        std::cout << "Please enter the number of cities to run the evolutionary algorithm with (10-13): ";
        int numCities = 0;
        while (numCities < 10 || numCities > 13) std::cin >> numCities;
        std::cout << "Please enter the number of tours to try in each generation (0-100,000): ";
        int numTours = 0;
        while (numTours <= 0 || numTours > 100000) std::cin >> numTours;
        std::cout << "Please enter the number of generations to run: (0-100,000): ";
        int numGenerations = 0;
        while (numGenerations <= 0 || numGenerations > 100000) std::cin >> numGenerations;
        std::cout << "Please enter the mutation percentage rate (0-100): ";
        float mutationRate = -1.0;
        while (mutationRate < 0 || mutationRate > 100) std::cin >> mutationRate;
        Evolution darwin(cities, numCities, numTours, numGenerations, mutationRate);
        return darwin.run();
    }
    void Menu::run() {
        std::cout << "Welcome to the Traveling Salesman Problem Solver" << std::endl;
        std::cout << "Now running a brute force check..." << std::flush;
        std::vector<BruteForceResults> bruteForceData;
        /*for (int i = 10; i <= 13; i++) {
            bruteForceData.push_back(runBF(i));
            std::cout << "..." << std::flush;
        }*/
        std::cout << std::endl;
        std::cout << "Complete" << std::endl;

        std::cout << "Now running an evolutionary algorithm to compare results" << std::endl;
        std::cout << "Enter Ctrl+C to stop the program at any time" << std::endl;
        std::vector<EvolutionResults> evolutionData;
        while (true) {
            EvolutionResults result = runGA();
            evolutionData.push_back(result);
            printGAResult(result);
        }
    }
    BruteForceResults Menu::runBF(int i) {
        Solver solver(cities, i);
        return solver.run();
    }
    void Menu::printGAResult(EvolutionResults result) {
        //do this
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
        std::cout << result.generations << std::endl;
        std:: cout << result.toursPerGeneration << std::endl;
        std:: cout << result.tourLength << std::endl;
        std:: cout << result.mutationRate << std::endl;
        std:: cout << result.timeToSolve << std::endl;
        std:: cout << result.bestTour << std::endl;
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    }