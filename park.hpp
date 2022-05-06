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
  //int (&distances)[9];
  // the park that is visisted before this parks
  // along the optimal path
  Park* predV;
  // constructor
  Park(int k, std::string n) {
    key = k; name = n; predV = nullptr; 
  }
  // overloaded equlity operator
  bool operator==(Park& other) const {
    if (key == other.key) {return true;}
    else {return false;}
  }
  bool friend operator<(const Park& r, const Park& l) {
    if (r.key < l.key) {return true;} else {return false;}}
  
};
