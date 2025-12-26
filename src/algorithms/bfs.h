#ifndef BFS_H
#define BFS_H

#include <vector>
#include <utility>
#include "../environment/maze.h"

std::pair<std::vector<std::pair<int,int>>, int> BFS(Maze &maze);

#endif
