#ifndef DFS_H
#define DFS_H

#include <vector>
#include <utility>
#include "../environment/maze.h"

std::pair<std::vector<std::pair<int,int>>, int> DFS(Maze &maze);

#endif
