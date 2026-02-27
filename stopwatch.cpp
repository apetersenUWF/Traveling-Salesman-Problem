/***************************************************************
  Ayden Petersen
  stopwatch.cpp
  Project 3

    This file contains the implementation of the StopWatch class, a simple
    timer class that can be used to save times and calculate elapsed time.
    Useful for post-run analysis of time complexity.
***************************************************************/
#include "stopwatch.hpp"
    StopWatch::StopWatch(): startTime(), endTime() {}
    void StopWatch::start() {
        startTime = std::chrono::high_resolution_clock::now();
    }
    void StopWatch::stop() {
        endTime = std::chrono::high_resolution_clock::now();
    }
    double StopWatch::getElapsedTime() {
        std::chrono::duration<double> elapsed = endTime - startTime;
        return elapsed.count();
    }