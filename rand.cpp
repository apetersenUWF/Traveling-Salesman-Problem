/***************************************************************
  Ayden Petersen
  rand.cpp
  Project 3

  This file contains the necessary logic to update array s with
  the next permutation, and to generate a random float on a defined
  interval
***************************************************************/
#include "rand.hpp"
#include <random>
bool perm1(int s[], int size) {
    int m, k, p , q, i;
    m = size-2;
    while(s[m]>s[m+1])
    {
      m = m - 1;
    }
    if (m < 0) return false;
    k = size-1;
    while(s[m] > s[k])
    {
      k = k - 1;
    }
    i = s[m];
    s[m] = s[k];
    s[k] = i;
    p = m + 1;
    q = size-1;
    while(p < q)
    {
      i = s[p];
      s[p] = s[q];
      s[q] = i;
      p++;
      q--;
    }
    return true;
}
float getRandomFloat(const float a, const float b) {//calculates a random float on the interval (a, b]
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());//uses the mersene twister engine for fast random numbers
  std::uniform_real_distribution<> distr(a, b);//defines the range from (a,b])
  float randomFloat = distr(generator);
  return randomFloat;
}
int getRandomInt(const int a, const int b) {
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());//uses the mersene twister engine for fast random numbers
  std::uniform_int_distribution<> distr(a, b);//defines the range from ascii a to z
  int randomInt = distr(generator);
  return randomInt;
}