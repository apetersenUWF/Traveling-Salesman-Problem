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
#include "rand.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////////////

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
        for (int j = 0; j <= tourLength; j++) {//generate the first tour, include every city except the starting point
            if (j != START_END_POINT) {//initialize tour and elitw to be the first permutation
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

///////////////////////////////////////////////////////////////////////

    void Evolution::processTour(int* tour) {
    float x = graph->getTourDistance(tour, tourLength);//check the value of this new tour
    if (x < bestTour) {//if its the best, save its value and save it to the elite
        bestTour = x;
        for (int i = 0; i < tourLength; i++) elite[i] = tour[i];//copy tour to the elite if its better
    }
}

///////////////////////////////////////////////////////////////////////
//Main GA Logic
    EvolutionResults Evolution::run() {
        EvolutionResults data;
        data.tourLength = tourLength;//save the current parameters for this run
        data.toursPerGeneration = toursPerGeneration;
        data.generations = generations;
        data.mutationRate = mutationRate;
        data.toursSearched = 0;
        StopWatch timer;
        timer.start();//start timing
        for (int i = 0; i < generations; i++) {
            int j = 0;
            //for every new generation, the elite will have a random number of offspring from [1, ELITE_OFFSPING_MAX]
            int eliteOffspringNum = getRandomInt(1, ELITE_OFFSPRING_MAX);
            int parent[tourLength];
            for (int k = 0; k < tourLength; k++) parent[k] = elite[k];//save the elite as the parent incase one of the children becomes the new elite
            for (int h = 0; h < eliteOffspringNum; h++) {
                int eliteChild[tourLength];
                for (int g = 0; g < tourLength; g++) eliteChild[g] = parent[g];//copy elite to its child
                mutate(eliteChild);//try to mutate the child
                processTour(eliteChild);
                data.toursSearched++;//count a tour searched
                j++;//count a tour from the generation
            }
            while (perm1(tour, tourLength) && j < toursPerGeneration) {//while there are still permutations and more tours in this generation, permute
                mutate(tour);//try mutating
                processTour(tour);
                data.toursSearched++;
                j++;
            }
        }
        timer.stop();//stop timing
        data.bestTour = bestTour;
        data.timeToSolve = timer.getElapsedTime();
        return data;
    }

    void Evolution::mutate(int* tour) {
        //can be 1 2 or 3 mutations
        //determined by a random roll
        //uses that same roll to calculate other parameters of the mutation
        //uses only 1 randoim number for each mutation for speed
        //a mutation swaps opposite array elements at random points
        float roll = getRandomFloat(0, 1);//gets random float between 0 and 1 for mutation chance
        roll *= 100;//convert to 0-100 percentage
        if (roll > mutationRate) return;//if mutation rate is 25%, numbers <= 25 will mutate
        //rolled a valid number, begin the mutation process
        int mutations;
        //muation count follows normal distribution
        if (roll < (0.68*mutationRate)) mutations = 1;
        else if (roll < (0.95*mutationRate)) mutations = 2;
        else mutations = 3;
        std::string rollstr = std::to_string(roll);//convert the float to a string to peel numbers off the end
        while (mutations != 0) {
            //for each mut, take the digit from the back of the random float
            //make that the swap index and swap with the index opposite of it
            int mutationPoint = rollstr.back() % tourLength;
            int mirrorPoint = (tourLength - 1) - mutationPoint;
            int temp = tour[mutationPoint];
            tour[mutationPoint] = tour[mirrorPoint];
            tour[mirrorPoint] = temp;
            mutations--;
        }
    }
