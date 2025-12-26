#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <utility>
#include "../environment/maze.h"

std::pair<std::vector<std::pair<int,int>>, int> AStar(Maze &maze);

#endif
