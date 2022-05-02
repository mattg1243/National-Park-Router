// adjancency matrix representation
// of all 9 parks with keys as indices:
// 0 - Yosemite
// 1 - Death Valley
// 2 - Joshua Tree
// 3 - Channel Islands
// 4 - Redwoods
// 5 - Point Reyes
// 6 - Sequoia & Kings Canyon
// 7 - Lassen
// 8 - Pinnacles

// distances according to Apple Maps
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