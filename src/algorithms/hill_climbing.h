#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H

#include <vector>
#include <utility>
#include "../environment/maze.h"

std::pair<std::vector<std::pair<int,int>>, int> HillClimbing(Maze &maze);

#endif
