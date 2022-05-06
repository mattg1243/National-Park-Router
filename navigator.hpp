#include <iostream>
#include <vector>
#include <algorithm>
#include "park.hpp"
#include "map.hpp"

using namespace std;

// utility function prototypes 
void printParkList();
class Navigator {
  private:
  // a vector that holds all of the park objects
  const std::vector<Park> parkVec = {
    Park(0, "Yosemite", map[0]),
    Park(1, "Death Valley", map[1]),
    Park(2, "Joshua Tree", map[2]),
    Park(3, "Channel Islands", map[3]),
    Park(4, "Redwoowds", map[4]),
    Park(5, "Point Reyes", map[5]),
    Park(6, "Sequoias", map[6]),
    Park(7, "Lassen", map[7]),
    Park(8, "Pinnacles", map[8])
  };
  // the adjacency matrix of distances between parks
  const int* adjMatrix = *map;

  public:
  // constructor
  Navigator() {};
  // find the shortes path according to depth first search
  int navigateDFS(int startKey);
  // find the shortest path according to a "nearest neighbor approach"
  int navigateNN(int startKey);
  // analyze the results of the competition between the algorithms
  void analyze();
  // start the CLI
  void startCLI();
  
};

int Navigator::navigateDFS(int startKey) {

  // create the return variable
  int shortestPath = INT_MAX;
  // create a vector with all parks minus the starting one
  std::vector<int> destinations;
  for (int i = 0; i < parkVec.size(); i++) {
    if (i != startKey) {
      destinations.push_back(i);
    }
  }
  // main do while loop that continues 
  // as long as there is another permutation
  // or possible route from starting point
  do {
    // current path accumulator
    int currentPath = 0;
    // compute the current path length with depth first traversal
    for (int i = 0; i < destinations.size(); i++) {



    }

  } while (std::next_permutation(destinations.begin(), destinations.end()));

  return shortestPath;
}

void Navigator::startCLI() {

  cout << "Welcome to the California National Park Road Trip Router!\n";
  cout << "Please enter a number that corresponds with the park you would like to start at or 0 to exit:\n";
  printParkList();

  string choice; 
  getline(cin, choice);

  while (choice != "0") {
    // do the complicated stuff in here
    cout << "\nthinking...\n";
    cout << "thinking...\n";
    cout << "thinking...\n\n";

    cout << "That was fun! Give it another try with a new starting point if you'd like or enter 0 to exit:\n";
    printParkList();

    getline(cin, choice);
  }

  cout << "Thanks for playing!" << endl;

}

// utility functions called by class methods
// prints out the list of parks and associated keys
void printParkList() {

  cout << "\t1. Yosemite\n";
  cout << "\t2. Death Valley\n";
  cout << "\t3. Joshua Tree\n";
  cout << "\t4. Channel Island\n";
  cout << "\t5. Redwoods\n";
  cout << "\t6. Point Reyes\n";
  cout << "\t7. Lassen\n";
  cout << "\t8. Pinnacles\n";

}