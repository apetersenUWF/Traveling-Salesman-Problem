#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP
const float RANDOM_FLOAT_LB = 0.0;//defines the default range of floats we want to generate
const float RANDOM_FLOAT_UB = 1.0;
  bool perm1(int s[], int size);//changes an array to its next permutation, modified in place
  float getRandomFloat(const float a = RANDOM_FLOAT_LB, const float b = RANDOM_FLOAT_UB);//generates a random float on (a,b]
  int getRandomInt(const int a, const int b);//generates a random int on (a,b]
#endif