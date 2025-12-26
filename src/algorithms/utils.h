#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <cmath>

inline int manhattan(std::pair<int,int> a, std::pair<int,int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

inline double euclidean(std::pair<int,int> a, std::pair<int,int> b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return std::sqrt(dx * dx + dy * dy);
}

inline int chebyshev(std::pair<int,int> a, std::pair<int,int> b) {
    int dx = std::abs(a.first - b.first);
    int dy = std::abs(a.second - b.second);
    return std::max(dx, dy);
}

#endif
