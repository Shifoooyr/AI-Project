# 🧩 AI Pathfinding Algorithms Project

## 📋 Overview
This project is a C++ implementation of popular pathfinding algorithms applied to maze-solving problems. It compares the performance of five algorithms: BFS, DFS, UCS, A*, and Hill Climbing on different maze difficulties.

## ✨ Key Features
- **Algorithms Implemented**:
  - Breadth-First Search (BFS)
  - Depth-First Search (DFS)
  - Uniform Cost Search (UCS)
  - A* Search
  - Hill Climbing
- **Maze Options**: Easy, Hard, and Insane difficulty levels
- **Visual Output**: Colored console display of paths
- **Performance Metrics**: Timing (averaged over 1000 runs) and statistics
- **Results Logging**: Saves detailed data to `results.txt`

## 🛠️ Requirements
- C++ compiler (GCC/g++ recommended, C++11+ support)
- Windows OS (for colored console output)
- Standard C++ libraries

## 🚀 Quick Start

### 1. Compile the Project
Use VS Code's build task (Ctrl+Shift+B) or run:
```bash
g++ src/environment/maze.cpp src/algorithms/bfs.cpp src/algorithms/dfs.cpp src/algorithms/ucs.cpp src/algorithms/astar.cpp src/algorithms/hill_climbing.cpp src/main.cpp -o build/main.exe
```

### 2. Run the Program
```bash
./build/main.exe
```

### 3. Choose a Maze
Select from 1 (Easy), 2 (Hard), or 3 (Insane).

### 4. View Results
- See the original maze and algorithm paths in the console
- Check `results.txt` for detailed performance data

## 📁 Project Structure
```
AI-Project/
├── src/
│   ├── main.cpp                 # Entry point, runs algorithms, handles output
│   ├── environment/
│   │   ├── maze.h              # Maze class and utilities
│   │   └── maze.cpp            # Maze definitions and printing
│   └── algorithms/
│       ├── utils.h             # Heuristic functions (Manhattan, Euclidean, Chebyshev)
│       ├── bfs.h & bfs.cpp     # BFS implementation
│       ├── dfs.h & dfs.cpp     # DFS implementation
│       ├── ucs.h & ucs.cpp     # UCS implementation
│       ├── astar.h & astar.cpp # A* implementation
│       └── hill_climbing.h & hill_climbing.cpp # Hill Climbing implementation
├── build/
│   └── main.exe                # Compiled executable
├── results.txt                 # Performance log
└── README.md                   # Project documentation
```

## 📊 Output Details

### Console Display
- Maze visualization with paths highlighted in color
- Per-algorithm stats: goal reached, path length, cost, optimality, nodes explored

### Results File (`results.txt`)
- Tabular comparison of all algorithms
- Timing in microseconds (avg. of 1000 runs)
- Maze-specific sections

## ⚠️ Important Notes
- **Windows Only**: Colored output relies on Windows console APIs
- **Timing Accuracy**: Measurements averaged over 1000 iterations
- **Path Costs**: Based on maze cell weights
- **Optimality Check**: Compares path costs to find the best solution
