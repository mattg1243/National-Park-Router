#include <string>
#include <vector>
// a class for national parks
class Park {
  public:
  // the numerical identifier for the park
  int key;
  // the name of the park
  std::string name;
  // an adjacency list representing the distances 
  // the index i = this.key will be set to 0 for consistency purposes
  int (&distances)[9];
  // the park that is visisted before this parks
  // along the optimal path
  Park* predV;
  // constructor
  Park(int k, std::string n, int (&d)[9]) : distances(d) {
    key = k; name = n; predV = nullptr; 
  }
  
};
