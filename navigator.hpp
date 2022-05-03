#include <iostream>
#include <vector>
#include <algorithm>
#include "park.hpp"
#include "map.hpp"

using namespace std;

class Navigator {
  private:
  // a vector that holds all of the park objects
  const std::vector<Park> parkVec = {
    Park(0, "Yosemite"),
    Park(1, "Death Valley"),
    Park(2, "Joshua Tree"),
    Park(3, "Channel Islands"),
    Park(4, "Redwoowds"),
    Park(5, "Point Reyes"),
    Park(6, "Sequoias"),
    Park(7, "Lassen"),
    Park(8, "Pinnacles"),
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

   // compute the current path length

  } while (std::next_permutation(destinations.begin(), destinations.end()));

  return shortestPath;
}

void Navigator::startCLI() {

  cout << "Welcome to the California National Park Road Trip Router!\n";
  cout << "Please enter a number that corresponds with the park you would like to start at or 0 to exit:\n";
  cout << "\t1. Yosemite\n";
  cout << "\t2. Death Valley\n";
  cout << "\t3. Joshua Tree\n";
  cout << "\t4. Channel Island\n";
  cout << "\t5. Redwoods\n";
  cout << "\t6. Point Reyes\n";
  cout << "\t7. Lassen\n";
  cout << "\t8. Pinnacles\n";

  string choice; 
  getline(cin, choice);

  while (choice != "0") {
    // do the complicated stuff in here
    cout << "\nthinking...\n";
    cout << "thinking...\n";
    cout << "thinking...\n\n";

    cout << "That was fun! Give it another try with a new starting point if you'd like or enter 0 to exit:\n";
    cout << "\t1. Yosemite\n";
    cout << "\t2. Death Valley\n";
    cout << "\t3. Joshua Tree\n";
    cout << "\t4. Channel Island\n";
    cout << "\t5. Redwoods\n";
    cout << "\t6. Point Reyes\n";
    cout << "\t7. Lassen\n";
    cout << "\t8. Pinnacles\n";

    getline(cin, choice);
  }

  cout << "Thanks for playing!" << endl;

}