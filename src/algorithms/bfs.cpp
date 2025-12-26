#include "bfs.h"
#include <queue> 
#include <algorithm>
#include <climits>
using namespace std;

pair<vector<pair<int,int>>, int> BFS(Maze &maze){
    int rows = maze.rows, cols = maze.cols;
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1,-1}));
    
    queue<pair<int,int>> q; 

    q.push(maze.start);
    dist[maze.start.first][maze.start.second] = 0;

    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    int discovered = 0;

    while(!q.empty()){
        pair<int,int> cur = q.front(); 
        q.pop();
        discovered++; 

        if(cur == maze.goal) break;

        for(int i=0; i<4; i++){
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if(maze.isValid(nx,ny) && dist[nx][ny] == INT_MAX){
                dist[nx][ny] = dist[cur.first][cur.second] + 1; 
                parent[nx][ny] = cur;
                q.push({nx,ny});
            }
        }
    }

    vector<pair<int,int>> path;
    if(dist[maze.goal.first][maze.goal.second] == INT_MAX) return {path, discovered};

    pair<int,int> p_cur = maze.goal;
    while(p_cur != make_pair(-1,-1)){
        path.push_back(p_cur);
        p_cur = parent[p_cur.first][p_cur.second];
    }
    reverse(path.begin(), path.end());

    return {path, discovered};
}