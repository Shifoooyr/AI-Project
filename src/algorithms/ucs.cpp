#include "ucs.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>  

using namespace std;

struct Node {
    pair<int,int> pos;
    int cost;
    bool operator>(const Node &other) const { return cost > other.cost; }
};

pair<vector<pair<int,int>>, int> UCS(Maze &maze){
    int rows = maze.rows, cols = maze.cols;
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1,-1}));

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    pq.push({maze.start, 0});
    dist[maze.start.first][maze.start.second] = 0;

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    int discovered = 0;

    while(!pq.empty()){
        Node cur = pq.top(); 
        pq.pop();

        if(cur.cost > dist[cur.pos.first][cur.pos.second]) continue;

        discovered++;
        if(cur.pos == maze.goal) break;

        for(int i=0;i<4;i++){
            int nx = cur.pos.first + dx[i];
            int ny = cur.pos.second + dy[i];
            
            if(maze.isValid(nx,ny)){
                int newCost = cur.cost + maze.getCost(nx, ny);
                
                if(newCost < dist[nx][ny]){
                    dist[nx][ny] = newCost;
                    parent[nx][ny] = cur.pos;
                    pq.push({{nx,ny}, newCost});
                }
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