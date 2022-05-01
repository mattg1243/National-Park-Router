#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
// adjacency matrix of all 9 parks
// defined in seperate file
#include "map.hpp"

using namespace std;

class Park {

  public:
  // the numerical identifier for the park
  int key;
  // the name of the park
  string name;
  // an adjacency list representing the distances 
  // the index i = this.key will be set to 0 for consistency purposes
  int distances[9];
  // the park that is visisted before this parks
  // along the optimal path
  Park* predV;
  Park(int k) { key = 0; distances[key] = INT_MAX; predV = nullptr; }
  

};

// the edege between vertices / parks
class Journey {

  public:
  // a two char array that stores 
  // the points the edge connects
  vector<Park> points;
  // the weight / distance of the edge
  int weight;
  // constructor
  Journey(int p1, int p2, int w) { 
    // push the endpoints to the vector
    points.push_back(Park(p1));
    points.push_back(Park(p2));
    // initialize weight
    weight = w;
  }

};

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

class Graph {

  private:
  // the matrix representation of the graph
  // 9 national parks in California
  int adjMatrix[9][9];
  // list of vertices
  vector<Park> verticesVec;
  // number of vertices in the graph
  int parksCount;

  public:
  // create a matrix with default values
  // based on given number of vertices
  Graph() { 
    // set parksCount 
    parksCount = 9;
    for (int i = 0; i < parksCount; i++) {
      for (int j = 0; j < parksCount; j++) {
        adjMatrix[i][j] = 0;
      }
    }
  }
  // member function to add edges between vertices
  void addEdge(int v1, int v2, int weight) {
    // create an instance of the Edge class
    // currently not doing anything with this object
    Journey e = Journey(v1, v2, weight);
    // add the edge to the matrix in both spots
    adjMatrix[v1][v2] = weight;
    adjMatrix[v2][v1] = weight;
  };
  // member function implementation of Dijsktras shortest path
  void dijsktras(int startV) {
    // array for distance values, from startV to i
    int distances[parksCount];
    // a boolean array that says if vertex i has been visited
    bool visitedSet[parksCount];
    // initialize this arrayy
    for (int i = 0; i < parksCount; i++) {
      distances[i] = INT_MAX;
      visitedSet[i] = false;
    }
    // set distance from startV to istself to 0
    distances[startV] = 0;
    // compute shortest paths
    for (int i = 0; i < 9; i++) {
      // "dequeue" the vertex with the shortest distance
      // that has not yet been visited
      int vCur = getMinDistance(distances, visitedSet);
      // this vertex has been visited
      visitedSet[vCur] = true;
      // update the distance values when all criteria are met
      for (int j = 0; j < 10; j++) {
        if (!visitedSet[j] && adjMatrix[i][j] && distances[i] != INT_MAX
          && distances[i] + adjMatrix[i][j] < distances[j]) {
            distances[j] = distances[i] + adjMatrix[i][j];
        }
      }
    }
    // print out the results
    for (int j = 0; j < parksCount; j++) {
      cout << "Distance from vertex " << j << "  =  " << distances[j] << endl;
    }
  }
};

// need a utility function that pulls in the data from an api call