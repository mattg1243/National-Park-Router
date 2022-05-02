#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
// adjacency matrix of all 9 parks
// defined in seperate file
#include "map.hpp"

using namespace std;


// this is out of place here i know
int getMinDistance(int d[], bool s[]) {
  int min = INT_MAX;
  int index;

  for (int i = 0; i < 10; i++) {
    if (s[i] == false && d[i] <= min) {
      min = d[i], index = i;
    }
  }

  return index;
}


// need a utility function that pulls in the data from an api call