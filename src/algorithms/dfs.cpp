#include "dfs.h"
#include <algorithm>
#include <vector>
using namespace std;

bool dfsUtil(Maze &maze, pair<int,int> cur, vector<vector<bool>> &visited, vector<pair<int,int>> &path, int &discovered) {
    int x = cur.first, y = cur.second;
    
    visited[x][y] = true;
    discovered++;
    path.push_back(cur);

    if(cur == maze.goal) return true;

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    for(int i=0; i<4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if(maze.isValid(nx, ny) && !visited[nx][ny]){
            if(dfsUtil(maze, {nx, ny}, visited, path, discovered)) return true;
        }
    }

    path.pop_back();
    return false;
}

pair<vector<pair<int,int>>, int> DFS(Maze &maze){
    int rows = maze.rows, cols = maze.cols;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int,int>> path;
    int discovered = 0;
    
    if(maze.isValid(maze.start.first, maze.start.second)) {
        dfsUtil(maze, maze.start, visited, path, discovered);
    }
    
    return make_pair(path, discovered);
}