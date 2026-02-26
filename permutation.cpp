#include "permutation.hpp"
/***************************************************************
  Ayden Petersen
  permutation.cpp
  Project 3

  This file contains the necessary logic to update array s with
  the next permutation.
***************************************************************/
  
void perm1(int s[], int size) {
    int m, k, p , q, i;
    m = size-2;
    while(s[m]>s[m+1])
    {
      m = m - 1;
    }
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
}
