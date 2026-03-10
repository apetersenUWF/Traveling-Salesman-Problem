# Traveling-Salesman-Problem-Project

This program contains two solutions to the traveling-salesman problem: a brute-force algorithm
that checks each permutation in the answer space to find the optimal solution, and a genetic algorithm
that simulates generations of trials with mutations and offspring to approximate the optimal solution
in a fraction of the time. The genetic algorithm can generally find a solution within 10-30% of optimal
in less than 0.1% of the time for n >= 13 where the problem takes the brute force over 5 minutes to solve.

This program considers a variation of the traveling salesman problem in which every city is connected
to every other city.

The genetic algorithm is a simple one which only keeps track of one elite tour at a time, with only simple
swapping mutations.

The purpose of the program is to provide the user with a menu to run the genetic algorithm and experiment
with different parameters in order to tune the algorithm so that it can closely approximate the optimal solution,
providing an alternative method of finding a decent solution to an otherwise intractable problem.

The algorithm will return 6 values that can be used to compare the genetic algorithm to the brute-force:

- ***Number of Cities***
- ***Brute-Force Optimal Cost***
- ***Brute-Force Time to Solve***
- ***Genetic Algorithm Cost***
- ***Genetic Algorithm Time to Solve***
- ***Percent of the Optimal Solution the GA found***

The last value is the one to try and optimize as it compares the genetic algorithm's solution to the
strictly optimal one.

These values will be displayed after each trial, as well as saved in the genetic-algorithm-results.csv file

# How to Use

This program comes with a Makefile, to use it run the command "make" in the command line interface.
This will generate an executable called "run".
Verify that the data files "distances.txt" and "brute-force-results.csv" are in the same directory as the executable.
Verify that the "distances.txt" file contains an adjacency matrix cooresponding to a complete graph with
no cities having a connection to themselves.

Issue the command "./run" in the command line to run the executable.
The program will first ask if you want to run the brute-force algorithm or use the results stored in the csv file.
It is recommended to do this everytime you run the brute force on a new system as the time to solve will vary
based on hardware. The brute-force will take 5-10 minutes to complete. After this the brute force results will be stored in
the csv file, then the program will prompt the user for parameters for the genetic algorithm. Parameters include:

- ***Number of Cities***
- ***Number of Tours per Generation***
- ***Number of Generations***
- ***Mutation Rate (%)***

In order to ensure a runtime under 1s, it is recommended you use values where (num tours) * (num generations) < 50,000

After this, the genetic algorithm will run with the provided values, the 6 values mentioned above will be printed to
the terminal and appended to the "genetic-algorithm-results.csv" file. You can repeat this as many times as you want,
press Ctrl+C to terminate the program and all results will be saved in the file. Excel can be used to view the results
more easily.
