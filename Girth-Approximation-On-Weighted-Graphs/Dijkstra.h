#ifndef DIJKSTRA
#define DIJKSTRA
#include "Graph.h"
using namespace std;
pair<double, node*> Dijkstra(graph&, node*, node*);
pair<double, node*> ModifiedDijkstra(graph&, node*, node*);
struct PairHasher {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
#endif