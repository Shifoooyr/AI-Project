#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "environment/maze.h"
#include "algorithms/bfs.h"
#include "algorithms/dfs.h"
#include "algorithms/ucs.h"
#include "algorithms/astar.h"
#include "algorithms/hill_climbing.h"
#include <climits>
#include <vector>
#include <string>

using namespace std;

struct Result {
    string name;
    vector<pair<int, int>> path;
    int discoveredNodes;
    long long time_taken_ns;
    int totalCost;
};

void printStatsAndFile(const Result &res, const pair<int, int> &goal, int shortestLength, ofstream &outFile) {
    bool reachedGoal = (!res.path.empty() && res.path.back() == goal);
    string pathLengthStr = reachedGoal ? to_string(res.path.size()) : "No path found";

    cout << endl << res.name << " Result : " << (reachedGoal ? "Goal Reached Successfully " : "Goal Not Reached ") << endl;
    cout << "-----------------------------\n";

    outFile << "========================================\n";
    outFile << "Algorithm: " << res.name << "\n";
    outFile << "----------------------------------------\n";
    outFile << "Reached Goal? " << (reachedGoal ? "Yes" : "No") << "\n";
    outFile << "Path Length: " << pathLengthStr << "\n";
    outFile << "Optimal for this Maze? " << ((reachedGoal && res.path.size() == shortestLength) ? "Yes" : "No") << "\n";
    outFile << "Discovered Nodes: " << res.discoveredNodes << "\n\n";
}

int main() {
    int choice;
    cout << "====================================\n";
    cout << "         MAZE SELECTION               \n";
    cout << "====================================\n";
    cout << "[1] Easy Maze\n";
    cout << "[2] Hard Maze\n";
    cout << "[3] Insane Maze\n";
    cout << "------------------------------------\n";
    cout << "Enter Your choice: ";
    cin >> choice;
    choice -= 1; 

    Maze maze = getMaze(choice);

    cout << "\nOriginal Maze:\n\n";
    maze.printMazeColored({});
    cout << "\n\n----------------------------------------------\n";

    vector<Result> results;
    {
        const int iterations = 1000;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            BFS(maze);
        }
        auto end = chrono::high_resolution_clock::now();
        long long total_time_ns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long time_taken_ns = total_time_ns / iterations;
        auto res = BFS(maze);
        int cost = 0;
        for (auto &p : res.first) cost += maze.getCost(p.first, p.second);
        Result r = { "BFS", res.first, res.second, time_taken_ns, cost };
        results.push_back(r);
    }
    {
        const int iterations = 1000;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            DFS(maze);
        }
        auto end = chrono::high_resolution_clock::now();
        long long total_time_ns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long time_taken_ns = total_time_ns / iterations;
        auto res = DFS(maze);
        int cost = 0;
        for (auto &p : res.first) cost += maze.getCost(p.first, p.second);
        Result r = { "DFS", res.first, res.second, time_taken_ns, cost };
        results.push_back(r);
    }
    {
        const int iterations = 1000;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            UCS(maze);
        }
        auto end = chrono::high_resolution_clock::now();
        long long total_time_ns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long time_taken_ns = total_time_ns / iterations;
        auto res = UCS(maze);
        int cost = 0;
        for (auto &p : res.first) cost += maze.getCost(p.first, p.second);
        Result r = { "UCS", res.first, res.second, time_taken_ns, cost };
        results.push_back(r);
    }
    {
        const int iterations = 1000;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            HillClimbing(maze);
        }
        auto end = chrono::high_resolution_clock::now();
        long long total_time_ns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long time_taken_ns = total_time_ns / iterations;
        auto res = HillClimbing(maze);
        int cost = 0;
        for (auto &p : res.first) cost += maze.getCost(p.first, p.second);
        Result r = { "Hill Climbing", res.first, res.second, time_taken_ns, cost };
        results.push_back(r);
    }
    {
        const int iterations = 1000;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            AStar(maze);
        }
        auto end = chrono::high_resolution_clock::now();
        long long total_time_ns = chrono::duration_cast<chrono::microseconds>(end - start).count();
        long long time_taken_ns = total_time_ns / iterations;
        auto res = AStar(maze);
        int cost = 0;
        for (auto &p : res.first) cost += maze.getCost(p.first, p.second);
        Result r = { "A*", res.first, res.second, time_taken_ns, cost };
        results.push_back(r);
    }

    int minCost = INT_MAX;
    for (auto &r : results) {
        if (!r.path.empty() && r.path.back() == maze.goal) {
            if (r.totalCost < minCost)
                minCost = r.totalCost;
        }
    }

    ofstream outFile("results.txt", ios::app);
    if (!outFile.is_open()) { cerr << "Error opening results.txt\n"; return 1; }

    outFile << "\n\n\n\n====================================================================================================================================\n";
    outFile << "                                                      Maze " << (choice + 1) << " Solving Results            \n";
    outFile << "====================================================================================================================================\n\n";

    outFile << "+---------------+---------------+---------------+---------------+---------------------+--------------------+-----------------------+\n";
    outFile << "| Algorithm     | Reached Goal  | Path Length   | Path Cost     | Optimal for Maze?   | Discovered Nodes   | Time Taken (us)       |\n";
    outFile << "+---------------+---------------+---------------+---------------+---------------------+--------------------+-----------------------+\n";

    for (auto &r : results) {
        bool reachedGoal = (!r.path.empty() && r.path.back() == maze.goal);
        string pathLengthStr = reachedGoal ? to_string(r.path.size()) : "N/A";
        string pathCostStr = reachedGoal ? to_string(r.totalCost) : "N/A";
        string optimalMaze = (reachedGoal && r.totalCost == minCost) ? "Yes" : "No";
        string timeStr = reachedGoal ? to_string(r.time_taken_ns) : "N/A";

        outFile << "| " << left << setw(13) << r.name 
                << " | " << setw(13) << (reachedGoal ? "Yes" : "No") 
                << " | " << setw(13) << pathLengthStr 
                << " | " << setw(13) << pathCostStr 
                << " | " << setw(19) << optimalMaze 
                << " | " << setw(18) << to_string(r.discoveredNodes) 
                << " | " << setw(21) << timeStr << " |\n";

        cout << "\n" << r.name << " Path:\n\n";
        maze.printMazeColored(r.path, 12);
        cout << "\n" << (reachedGoal ? "Path is successfully found!" : "No path found.") << "\n";
        cout << "\n\n----------------------------------------------\n";
    }
    outFile << "+---------------+---------------+---------------+---------------+---------------------+--------------------+-----------------------+\n";

    outFile.close();
    return 0;
}