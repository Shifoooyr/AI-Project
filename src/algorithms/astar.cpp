#include "astar.h"
#include "utils.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct AStarNode {
    pair<int, int> position;
    int g_score; 
    int h_score; 
    int f_score() const { return g_score + h_score; }

    
    bool operator>(const AStarNode& other) const {
        return f_score() > other.f_score();
    }
};

pair<vector<pair<int, int>>, int> AStar(Maze& maze) {
    const int rows = maze.rows;
    const int cols = maze.cols;

    
    vector<vector<int>> min_g_score(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int, int>>> came_from(rows, vector<pair<int, int>>(cols, {-1, -1}));

    priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> open_set;

    int initial_h = manhattan(maze.start, maze.goal);
    min_g_score[maze.start.first][maze.start.second] = 0;
    open_set.push({maze.start, 0, initial_h});

    int discovered_count = 0;
    const int dr[] = {-1, 1, 0, 0}; 
    const int dc[] = {0, 0, -1, 1}; 

    while (!open_set.empty()) {
        AStarNode current = open_set.top();
        open_set.pop();

        if (current.g_score > min_g_score[current.position.first][current.position.second]) {
            continue;
        }

        discovered_count++;

        if (current.position == maze.goal) break;

        for (int i = 0; i < 4; ++i) {
            int nr = current.position.first + dr[i];
            int nc = current.position.second + dc[i];

            if (maze.isValid(nr, nc)) {
                int weight = maze.getCost(nr, nc);
                int tentative_g_score = current.g_score + weight;

                if (tentative_g_score < min_g_score[nr][nc]) {
                    min_g_score[nr][nc] = tentative_g_score;
                    came_from[nr][nc] = current.position;
                    
                    int h = manhattan({nr, nc}, maze.goal);
                    open_set.push({{nr, nc}, tentative_g_score, h});
                }
            }
        }
    }

    vector<pair<int, int>> final_path;
    if (min_g_score[maze.goal.first][maze.goal.second] == INT_MAX) {
        return {final_path, discovered_count};
    }

    for (pair<int, int> temp = maze.goal; temp != make_pair(-1, -1); temp = came_from[temp.first][temp.second]) {
        final_path.push_back(temp);
    }
    reverse(final_path.begin(), final_path.end());

    return {final_path, discovered_count};
}