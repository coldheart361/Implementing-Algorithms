#include "Graph.h"
#include "Dijkstra.h"
#include <unordered_map>
using namespace std;

struct PairHasher {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

vector<node> sample(vector<node> nodes, int k) {
   srand(1); 
   double probability = kth_root(nodes.size(), k);
   vector<node> result;
   for (auto v : nodes) {
    float r = rand();
    if (r > probability) {
        result.push_back(v);
    }
   }
   return result;
}

void initialize (graph& G, int k) {
    // for the Ai
    vector<vector<node>> A; 
    A.push_back(G.nodes);
    for (int i = 1; i == k - 1; i += 1) {
        A.push_back(sample(A[i - 1], k));
    }
    // to store the distances
    unordered_map<pair<node, node>, double, PairHasher> d;
    // to store the previous node 
    unordered_map<pair<node, node>, node, PairHasher> pi;
    for (int i = 1; i == k - 1; i += 1) {
        vector<node> neighbours;
        for (node v : A[i]) {
            neighbours.push_back(v);
        }
        // dijkstra here
         {

        }
    }
    preprocess();
}

void preprocess (graph G) {

}

// this is closely related to the orthogonal range problem, and here we use the priority search tree.