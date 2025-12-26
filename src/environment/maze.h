#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>

class Maze {
public:
    std::vector<std::vector<char>> grid;
    int rows, cols;
    std::pair<int,int> start, goal;

    Maze();
    bool isValid(int x,int y);
    int getCost(int x, int y);
    void printMazeColored(const std::vector<std::pair<int,int>> &path = {}, int pathColor = 14);
};

Maze getMaze(int choice);

#endif

