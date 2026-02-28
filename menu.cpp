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
#include <fstream>
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
        if (!createOutputFiles()) return;//try to create output files, if it fails exit program
        std::cout << "Welcome to the Traveling Salesman Problem Solver" << std::endl;
        std::cout << "Now running a brute force check..." << std::flush;
        std::vector<BruteForceResults> bruteForceData;
        for (int i = 10; i <= 11; i++) {
            bruteForceData.push_back(runBF(i));
            std::cout << "..." << std::flush;
        }
        std::cout << std::endl;
        std::cout << "Complete" << std::endl;
        saveBFData(bruteForceData);
        std::cout << "Now running an evolutionary algorithm to compare results" << std::endl;
        std::cout << "Enter Ctrl+C to stop the program at any time" << std::endl;
        while (true) {
            EvolutionResults result = runGA();
            result.percentOptimal = (result.bestTour / bruteForceData[result.tourLength - 10].bestTour) * 100;
            result.percentOptimalTime = (result.timeToSolve / bruteForceData[result.tourLength - 10].timeToSolve) * 100;
            appendGAData(result);
            printGAResult(result);
        }
    }
    BruteForceResults Menu::runBF(int i) {
        Solver solver(cities, i);
        return solver.run();
    }
    void Menu::printGAResult(EvolutionResults& result) {
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
        std::cout << result.generations << std::endl;
        std:: cout << result.toursPerGeneration << std::endl;
        std:: cout << result.tourLength << std::endl;
        std:: cout << result.mutationRate << std::endl;
        std:: cout << result.timeToSolve << std::endl;
        std:: cout << result.bestTour << std::endl;
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    }
    bool Menu::createOutputFiles() {
        std::ofstream bf_ofs("brute-force-results.csv");//open the output files to hold data
        std::ofstream ga_ofs("genetic-algorithm-results.csv");
        if (!bf_ofs.is_open() || !ga_ofs.is_open()) {//if a file doesnt open terminate the program before doing anything
            std::cout << "Failed to open output file, terminating" << std::endl;
            return false;
        }
        bf_ofs << "#Cities" << "," << "Best" << "," << "TTS(s)" << "," << "Searches" << std::endl;//initialize headers;
        ga_ofs << "#Cities" << ",";
        ga_ofs << "Gens" << ",";
        ga_ofs << "ToursPerGen" << ",";
        ga_ofs << "Mut%" << ",";
        ga_ofs << "Best" << ",";
        ga_ofs << "TTS(s)" << ",";
        ga_ofs << "Searches" << ",";
        ga_ofs << "Optim%" << ",";
        ga_ofs << "OptimT%" << std::endl;
        bf_ofs.close();
        ga_ofs.close();
        return true;
    }
    bool Menu::saveBFData(std::vector<BruteForceResults>& bfData) {
        std::ofstream bf_ofs("brute-force-results.csv", std::ios::app);//open the output files to hold data
        if (!bf_ofs.is_open()) return false;
        for (long unsigned int i = 0; i < bfData.size(); i++) {
            bf_ofs << bfData[i].tourLength << ",";
            bf_ofs << bfData[i].bestTour << ",";
            bf_ofs << bfData[i].timeToSolve << ",";
            bf_ofs << bfData[i].toursToSolve << std::endl;
        }
        bf_ofs.close();
        return true;
    }
    bool Menu::appendGAData(EvolutionResults& gaData) {
        std::ofstream ga_ofs("genetic-algorithm-results.csv", std::ios::app);//open the output files to hold data
        if (!ga_ofs.is_open()) return false;
        ga_ofs << gaData.tourLength << ",";
        ga_ofs << gaData.generations << ",";
        ga_ofs << gaData.toursPerGeneration << ",";
        ga_ofs << gaData.mutationRate<< ",";
        ga_ofs << gaData.bestTour << ",";
        ga_ofs << gaData.timeToSolve<< ",";
        ga_ofs << gaData.toursSearched << ",";
        ga_ofs << gaData.percentOptimal << ",";
        ga_ofs << gaData.percentOptimalTime << std::endl;
        ga_ofs.close();
        return true;
    }