#include "hill_climbing.h"
#include <algorithm>
#include <map>
#include <cmath>
#include "utils.h"
#include <climits> 

using namespace std;

pair<vector<pair<int,int>>, int> HillClimbing(Maze &maze){
    pair<int,int> cur = maze.start;
    vector<pair<int,int>> path = {cur};
    map<pair<int,int>, bool> visited;
    visited[cur] = true;
    int discovered = 1; 

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    while(cur != maze.goal){
        pair<int,int> nextMove = {-1, -1};
        int minVal = INT_MAX; 

        for(int i=0;i<4;i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            pair<int,int> np = {nx,ny};

            if(maze.isValid(nx,ny) && !visited[np]){
                int val = manhattan(np, maze.goal); 
                if(val < minVal){
                    minVal = val;
                    nextMove = np;
                }
            }
        }

        if(nextMove.first == -1 || minVal >= manhattan(cur, maze.goal)) {
            break; 
        }

        cur = nextMove;
        path.push_back(cur);
        visited[cur] = true;
        discovered++;
    }

    return make_pair(path, discovered);
}