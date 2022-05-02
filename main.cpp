#include <iostream>
#include "park.hpp"

using namespace std;

int main() {

// instantiate all 9 parks in California
Park* Yosemite = new Park(0, "Yosemite");
Park DeathValley = Park(1, "Death Valley");
Park JoshuaTree = Park(2, "Joshua Tree");
Park ChannelIslands = Park(3, "Channel Islands");
Park Redwoods = Park(4, "Redwoowds");
Park PointReyes = Park(5, "Point Reyes");
Park Sequoias = Park(6, "Sequoias");
Park Lassen = Park(7, "Lassen");
Park Pinnacles = Park(8, "Pinnacles");

cout << "Yosemite object test: \nkey - " << Yosemite->key << "\nname - " << Yosemite->name << "\n";

}