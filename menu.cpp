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
#include "rand.hpp"

///////////////////////////////////////////////////////////////////////
    Menu::Menu() {cities = new Graph(DEFAULT_FILE);}
    Menu::~Menu() {delete cities;}
///////////////////////////////////////////////////////////////////////
//Main algorithm run logic
    BruteForceResults Menu::runBF(int i) {
        Solver solver(cities, i);
        return solver.run();
    }

    EvolutionResults Menu::runGA() {
        //takes some io parameters from the user and runs the ga with them
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
        if (!createGAOutputFile()) return;//try to create output file, if it fails exit program
        std::cout << "Welcome to the Traveling Salesman Problem Solver" << std::endl;
        std::cout << "Input an X to run the brute-force for 10-13 citites" << std::endl;
        std::cout << "Any other input will skip the brute force and use data from the table" << std::endl;
        std::cout << "Running the brute-force will overwrite previous table data" << std::endl;
        std::vector<BruteForceResults> bruteForceData;
        char userInput = '$';
        std::cin >> userInput;
        if (userInput == 'X') {
            if (!createBFOutputFile()) return;
            std::cout << "Now running a brute force check..." << std::flush;
            for (int i = 10; i <= 13; i++) {//run brute force for 10-13 cities
                bruteForceData.push_back(runBF(i));
                std::cout << "..." << std::flush;
            }
            std::cout << std::endl;
            std::cout << "Complete" << std::endl;
            saveBFData(bruteForceData);
            std::cout << "Results saved to brute-force-results.csv" << std::endl;
        }
        else {bruteForceData = loadBFData();}//user chose to skip brute-force, load predefined data
        std::cout << "Now running an evolutionary algorithm to compare results" << std::endl;
        std::cout << "Limit (G x N) < 50000 for the algorithm to complete in under a second" << std::endl;
        std::cout << "Enter Ctrl+C to stop the program at any time" << std::endl;
        while (true) {
            //until the user terminates
            //promp the user for parameters
            //run the ga
            //append the results to the data file
            //print the results to the terminal
            EvolutionResults result;
            if (userInput == '~') result = runRandomGA();//entry to run lots of random trials
            else result = runGA();

            result.bfOptimal = bruteForceData[result.tourLength - 10].bestTour;
            result.bfOptimalTime = bruteForceData[result.tourLength - 10].timeToSolve;
            result.percentOptimal = (result.bestTour / result.bfOptimal) * 100;
            result.percentOptimalTime = (result.timeToSolve / result.bfOptimalTime) * 100;
            appendGAData(result, bruteForceData);
            if (userInput != '~') printGAResult(result);
        }
    }

    EvolutionResults Menu::runRandomGA() {
        int numCities, numTours, numGenerations;
        float mutationRate;

        numCities = getRandomInt(10, 13);
        numTours = getRandomInt(500, 10000);
        numGenerations = 100000/numTours;
        mutationRate = getRandomFloat(0, 70);
        Evolution darwin(cities, numCities, numTours, numGenerations, mutationRate);
        return darwin.run();
    }
///////////////////////////////////////////////////////////////////////
//Terminal and Filo I/O Logics

    void Menu::printGAResult(EvolutionResults& result) {//prints ga results to the terminal
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
        std::cout << result.tourLength << " cities" << std::endl;
        std:: cout << "Brute-Force cost = " << result.bfOptimal << std::endl;
        std:: cout << "Brute-Force TTS = " << result.bfOptimalTime << " s" << std::endl;
        std:: cout << "GA cost = " << result.bestTour << std::endl;
        std:: cout << "GA TTS = " << result.timeToSolve << " s" << std::endl;
        std:: cout << "GA Optimal Percentage = " << result.percentOptimal << "%" << std::endl;
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
    }

    bool Menu::createGAOutputFile() {
        std::ofstream ga_ofs("genetic-algorithm-results.csv");
        if (!ga_ofs.is_open()) {//if a file doesnt open terminate the program before doing anything
            std::cout << "Failed to open output file, terminating" << std::endl;
            return false;
        }
        ga_ofs << "#Cities" << ",";
        ga_ofs << "BF Cost" << ",";
        ga_ofs << "BF TTS (s)" << ",";
        ga_ofs << "GA Cost" << ",";
        ga_ofs << "GA TTS (s)" << ",";
        ga_ofs << "Optim%" << std::endl;
        ga_ofs.close();
        return true;
    }

    bool Menu:: createBFOutputFile() {
        std::ofstream bf_ofs("brute-force-results.csv");//open the output files to hold data
        if (!bf_ofs.is_open()) {//if a file doesnt open terminate the program before doing anything
            std::cout << "Failed to open output file, terminating" << std::endl;
            return false;
        }
        bf_ofs << "#Cities" << "," << "Best" << "," << "TTS(s)" << "," << std::endl;//initialize headers;
        bf_ofs.close();
        return true;
    }

    bool Menu::saveBFData(std::vector<BruteForceResults>& bfData) {
        std::ofstream bf_ofs("brute-force-results.csv", std::ios::app);//open the output files to hold data
        if (!bf_ofs.is_open()) return false;
        for (long unsigned int i = 0; i < bfData.size(); i++) {
            bf_ofs << bfData[i].tourLength << ",";
            bf_ofs << bfData[i].bestTour << ",";
            bf_ofs << bfData[i].timeToSolve << std::endl;
        }
        bf_ofs.close();
        return true;
    }

    std::vector<BruteForceResults> Menu::loadBFData() {
        std::ifstream bf_ifs("brute-force-results.csv");
        std::vector<BruteForceResults> bfresults;
        if (!bf_ifs.is_open()) return bfresults;//file didnt open, return
        std::string header;
        getline(bf_ifs, header);//read and ignore header line
        for (int i = 0; i < 4; i++) {
            std::string line;
            BruteForceResults x;
            getline(bf_ifs, line, ',');
            x.tourLength = stoi(line);
            getline(bf_ifs, line, ',');
            x.bestTour = stof(line);
            getline(bf_ifs, line);
            x.timeToSolve = stod(line);
            bfresults.push_back(x);
        }
        bf_ifs.close();
        return bfresults;
    }
    
    bool Menu::appendGAData(EvolutionResults& gaData, std::vector<BruteForceResults>& bfData) {
        std::ofstream ga_ofs("genetic-algorithm-results.csv", std::ios::app);//open the output files to hold data
        if (!ga_ofs.is_open()) return false;
        ga_ofs << gaData.tourLength << ",";
        ga_ofs << bfData[gaData.tourLength-10].bestTour << ",";
        ga_ofs << bfData[gaData.tourLength-10].timeToSolve << ",";
        ga_ofs << gaData.bestTour << ",";
        ga_ofs << gaData.timeToSolve<< ",";
        ga_ofs << gaData.percentOptimal << std::endl;
        ga_ofs.close();
        return true;
    }
