# National Park Router

### Intro:

For my project, I choose to try to come up with a solution to the classic traveling salesman problem, although I had never heard of it before starting this project. My idea was to write a program that could use some sort of graph algorithm that we learned (as these were the most interesting to me) to try to find the shortest path that visits all 9 of the national parks in California. Putting this problem into algorithmic terms, I needed to figure out a way to visit every vertex in a graph only once while every vertex is connected to every other vertex. This seemed like a simple problem until I started digging into it and really thinking about what algorithm would help me solve this problem. I first thought maybe a combination of Dijkstra’s and Floyd-Warshall to create some sort of elaborate solution, however neither of those algorithms really got me anywhere since every vertex was connected to every other one, so the shortest path to every vertex was simply the direct path between the two. While the solution that I came up with is definitely not scalable above maybe 10-15 vertices, I ended up using a slightly modified version of the Depth First Search algorithm to traverse every variation of the graph and store the shortest path.

---

### High Level Overview:

I’m using a 9x9 adjacency matrix to represent the graph of all the National Parks. I manually collected and input this data from Apple Maps which took a bit of time:

```cpp
int map[9][9] = {
  // from Yosemite
  {0, 401, 387, 293, 486, 201, 143, 324, 216},
  // from Death Valley
  {401, 0, 237, 296, 764, 544, 321, 176, 409},
  // from Joshua Tree
  {387, 237, 0, 194, 826, 529, 306, 688, 394},
  // from Channel Islands
  {293, 296, 194, 0, 649, 364, 213, 541, 198},
  // from Redwoods
  {486, 764, 826, 649, 0, 314, 581, 231, 466},
  // from Point Reyes
  {201, 544, 529, 364, 314, 0, 301, 248, 171},
  // from Sequoia
  {143, 321, 306, 213, 581, 301, 0, 425, 181},
  // from Lassen
  {324, 176, 688, 541, 231, 248, 425, 0, 358},
  // from Pinnacles
  {216, 409, 394, 198, 466, 171, 181, 358, 0},
};
```

I created a few classes to help me organize the data and functions into associated objects:

```cpp
class Park {
	public:
  // the numerical identifier for the park
  int key;
  // the name of the park
  std::string name;
  // the park that is visisted before this parks
  // along the optimal path
  Park* predV;
  // constructor
  Park(int k, std::string n) {
    key = k; name = n; predV = nullptr; 
  }
  // overloaded operators
  bool operator==(Park& other) const {
    if (key == other.key) {return true;}
    else {return false;}
  }
  bool friend operator<(const Park& r, const Park& l) {
    if (r.key < l.key) {return true;} else {return false;}}
}
```

```cpp
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
  // start the CLI
  void startCLI();
  
};
```

---

### Taking a Closer Look:

Now that you have a good idea of how this program is laid out from a higher level, let’s take a look at whats going on under the hood:

```cpp
int Navigator::navigateDFS(Park startPark) {

  // create the return variable
  int shortestPath = INT_MAX;
  // variable that tracks how many different routes are tested
  int numberOfIters = 0;
  // create a vector of all parks minues the starting park that is shuffled
  // to a new unique order after main loop finishes
  std::vector<Park> destinations;
  // a parallel vector of ints used for permutation
  std::vector<int> destinationsInts;
  // one more vector storing the sequence of parks to visit
  std::vector<Park> journey;
  for (int i = 0; i < parkVec.size(); i++) {
    if (i != startPark.key) {
      destinationsInts.push_back(i);
    }
  }
  // main do while loop that continues 
  // as long as there is another permutation
  // or possible route from starting point
  do {
    numberOfIters++;
    // current path accumulator
    int currentPath = 0;
    // the key of the last park visited
    int lastPark = startPark.key;
    // set up the newly shuffled vector
    destinations.clear();
    for (int i = 0; i < parkVec.size(); i++) {
      int index = destinationsInts[i];
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
        // reassign last park
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

  cout << "\nOptimal Path found after testing " << numberOfIters << " different routes:\n";
  for (int i = 0; i < journey.size() - 1; i++) {
    cout << journey[i].name << " -> ";
  }
  cout << journey[7].name << '\n';

  return shortestPath;
}
```

That’s a lot of code, but hopefully my comments were able to help you make sense of what’s going on here. Basically, I am doing the basic Depth First Search algorithm here, defining a set of visited vertices and a stack to pop from to decide which vertex is visited first. This same basic process is repeated a ton of times (40,320 times to be exact) until every variation of that stack, or order of parks visited, is exhausted, guaranteeing the shortest possible route is found. 

I knew this idea would work, however it was actually much harder than it sounds to put it into code. I tried a couple of very sloppy methods to get every different variation of the route, however after spending time with the documentation, I stumbled upon exactly what I was looking for in the function *`next_permutation()`.* This function does exactly what I was trying to accomplish.

Per the documentation:

> “*Rearranges the elements in the range [first, last) into the next [lexicographically](https://www.cplusplus.com/lexicographical_compare) greater permutation. A permutation is each one of the [first, last) N! possible arrangements the elements can take (where N is the number of elements in the range). Different permutations can be ordered according to how they compare to each other; The first such-sorted possible permutation (the one that would compare lexicographically smaller to all other permutations) is the one which has all its elements sorted in ascending order, and the largest has all its elements sorted in descending order.”*
> 

source: [https://www.cplusplus.com/reference/algorithm/next_permutation/?kw=next_permutation](https://www.cplusplus.com/reference/algorithm/next_permutation/?kw=next_permutation)

I was very happy to find this function, as that was my biggest challenge I had encountered so far. However, if you look closely at the code, you’ll notice that I am choosing not to take the permutation of the vector of Park objects, but rather a parallel vector of integers that I used for arranging the Park object vector. I had originally been calling `*next_permutation()`* on the vector of Park objects, however this wasn’t ideal because it required using an overloaded operator to check the keys of the objects instead of directly comparing two integers in memory. Seeing as I really only needed to shuffle the index of the Park object, I decided to use the parallel integer vector approach as it seemed to be simpler and more efficient, even though it’s a bit more confusing.

---

### Example Run:

When doing projects like this, I always aim to make a cool command line interface so that people can test it out for themselves. It’s not only a fun and satisfying way to see your program in action, it also really makes you appreciate how something that looks and functions so simply can be so full of abstraction and complexity. Here’s a couple of test runs on my machine:

![Screen Shot 2022-05-08 at 10 35 51 PM](https://user-images.githubusercontent.com/76641882/167711093-757d9300-4434-4d1b-a224-6a6c91c5827b.png)
This is the prompt that first appears in the console when you run the program. Lets assume I want to start at Joshua Tree:

![Screen Shot 2022-05-08 at 10 36 28 PM](https://user-images.githubusercontent.com/76641882/167711126-3fdb07d7-d07b-4d58-bb22-770dcb9aba0b.png)

---

### Potential Improvements:

Something that I think would be really cool to add to this project is an integration with the Google Maps API that would be part of the Park class constructor. Maybe an argument for the constructor would be the Maps location ID of the park or something like that and from there, distances to every other Park could be pulled from the API and added to the adjacency matrix automatically. That seems like it could be tricky to actually put in code but if works, it would make adding parks a whole lot less tedious than manually entering a new row and column.

Aside from that, I also think I could probably refine the actual Depth First Search algorithm and all of the operations done when traversing the graph. I used a lot of vectors and can’t help but feel that I may have taken a couple unnecessary steps along the way to finding the shortest path.

### Conclusion:

When I first set out to solve this problem, I had no idea that I had just stumbled upon an NP-Hard problem. It seemed simple enough, there are many more complicated, obscure things that have elegant solutions and this seemed like a pretty “every day” problem to me. If anyone has a real efficient solution to this problem, I would bet its Amazon; I could only imagine how much time and man power they have put into solving this very same problem in an algorithmic way. All in all, I had a great time trying to come up with a solution to this challenging problem and feel pretty accomplished that I did find one at all!
