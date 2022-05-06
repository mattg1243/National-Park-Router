#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>
#include "park.hpp"
#include "map.hpp"

using namespace std;

// utility function prototypes 
void printParkList();
class Navigator {
  private:
  // a vector that holds all of the park objects
  const std::vector<Park> parkVec = {
    Park(0, "Yosemite"),
    Park(1, "Death Valley"),
    Park(2, "Joshua Tree"),
    Park(3, "Channel Islands"),
    Park(4, "Redwoowds" ),
    Park(5, "Point Reyes"),
    Park(6, "Sequoias"),
    Park(7, "Lassen"),
    Park(8, "Pinnacles")
  };
  // the adjacency matrix of distances between parks
  const int* adjMatrix = *map;

  public:
  // constructor
  Navigator() {};
  // find the shortes path according to depth first search
  int navigateDFS(Park startPark);
  // find the shortest path according to a "nearest neighbor approach"
  int navigateNN(int startKey);
  // analyze the results of the competition between the algorithms
  void analyze();
  // start the CLI
  void startCLI();
  
};

int Navigator::navigateDFS(Park startPark) {

  // create the return variable
  int shortestPath = INT_MAX;
  // create a vector of all parks - starting park that is shuffled
  // to a new unique order after main loop finishes
  std::vector<Park> destinations;
  // a parallel vector of ints used for permutation
  // could not get that to work when comparing custom class objects
  // one more vector storing the sequence of parks to visit
  std::vector<Park> journey;
  std::vector<int> destinationsInts;
  for (int i = 0; i < parkVec.size(); i++) {
    if (i != startPark.key) {
      destinationsInts.push_back(i);
    }
  }
  // main do while loop that continues 
  // as long as there is another permutation
  // or possible route from starting point
  do {
    // current path accumulator
    int currentPath = 0;
    // the key of the last park visited
    int lastPark = startPark.key;
    // set up the newly shuffled vector
    destinations.clear();
    for (int i = 0; i < parkVec.size(); i++) {
      int index = destinationsInts[i];
      cout << "___INDEX___  :  " << index << endl;
      destinations.push_back(parkVec[index]);
    }
    // create a stack that holds the unique permutation of destinations
    // using deque here for performance benefits
    std::deque<Park> stack; 
    stack.push_front(destinations[0]);
    // create a set that will be filled with visited parks
    std::set<Park> visitedParks;
    // compute the current path length with depth first traversal
    while (!stack.empty()) {
      // pop from the stack 
      Park currentPark = stack.front();
      stack.pop_front();
      // check if park has been visited already
      if (visitedParks.count(currentPark) != 0) {
        continue;
      }
      else {
        // add the distance from the previous park to this one
        currentPath += map[lastPark][currentPark.key];
        // reassing last park
        lastPark = currentPark.key;
        // add this park to visitedParks set
        visitedParks.insert(currentPark);
        // add other parks to the stack 
        for (int i = 0; i < destinations.size(); i++) {
          if (visitedParks.count(destinations[i]) != 0) {
            continue;
          } else {
            stack.push_front(destinations[i]);
          }
        }
      }
    }
    // check if a shorter path has been found
    if (currentPath < shortestPath) {
      shortestPath = currentPath; 
      // save the route
      std::vector<Park> journeyTemp(visitedParks.begin(), visitedParks.end());
      journey = journeyTemp;
    }

  } while (std::next_permutation(destinationsInts.begin(), destinationsInts.end()));

  cout << "\nOptimal Path:\n";
  cout << startPark.name << endl;
  for (int i = 0; i < journey.size(); i++) {
    cout << journey[i].name << "\n";
  }

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
    int dfsShortestPath = Navigator::navigateDFS(parkVec[stoi(choice) - 1]);

    cout << "\nThe shortest path as found by DFS is " << dfsShortestPath << " miles.\n\n";

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