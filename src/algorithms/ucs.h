#ifndef UCS_H
#define UCS_H

#include <vector>
#include <utility>
#include "../environment/maze.h"

std::pair<std::vector<std::pair<int,int>>, int> UCS(Maze &maze);

#endif
