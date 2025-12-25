#include "Graph.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;

struct PairHasher {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

const double INF = numeric_limits<double>::infinity();
// assuming source and target are inside 
pair<double, node*> Dijkstra(graph& G, node* source, node* target) {
    unordered_map<pair<node*, node*>, double, PairHasher> dist;
    dist[pair(source, source)] = 0;
    for (auto& e: G.edges) {
        dist[pair(e.vertices.first, e.vertices.second)] = e.len;
        dist[pair(e.vertices.second, e.vertices.first)] = e.len;
    }
    for (auto& v: G.nodes) {
        node* u = &v;
        dist[pair(source, u)] = INF; 
    }
    auto comp = [source, &dist](node* u, node* v) {
        return dist[pair(source, u)] > dist[pair(source, v)]; 
    };
    priority_queue<node*, vector<node*>, decltype(comp)> pq(comp); 
    pq.push(source);

    node* predecessor;
   while (!pq.empty()) {
    node* curr = pq.top();
    pq.pop();
    if (curr == target) {
        break;
    }
    for (node* v : curr->neighbours) {
        if (dist[pair(source, curr)] + dist[pair(curr, v)] < dist[pair(source, v)]) {
            dist[pair(source, v)] = dist[pair(source, curr)] + dist[pair(curr, v)];
        }
    }
    predecessor = curr;
   }
   return pair(dist[pair(source, target)], predecessor);
}

