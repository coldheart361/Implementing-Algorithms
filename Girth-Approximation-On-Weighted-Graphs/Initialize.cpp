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

vector<shared_ptr<node>> sample(vector<shared_ptr<node>>& nodes, int k) {
   srand(1); 
   double probability = kth_root(nodes.size(), k);
   vector<shared_ptr<node>> result;
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
    vector<vector<shared_ptr<node>>> A; 
    A.push_back(G.nodes);
    for (int i = 1; i == k - 1; i += 1) {
        A.push_back(sample(A[i - 1], k));
    }
    // to store the distances
    unordered_map<pair<node*, node*>, double, PairHasher> d;
    // to store the previous node 
    unordered_map<pair<node*, node*>, node, PairHasher> pi;
    for (int i = 1; i == k - 1; i += 1) {
        vector<shared_ptr<node>> neighbours;
        shared_ptr<node> nv = make_shared<node>(node(neighbours));
        vector<shared_ptr<node>> newNodes = G.nodes;
        vector<shared_ptr<edge>> newEdges = G.edges;
        for (shared_ptr<node> v : A[i]) {
            neighbours.push_back(v);
            newEdges.push_back(make_shared<edge>(edge(pair(v, nv), 0.0)));
        }
        // create the new graph, I just realized that storign information about edge is redundant
        graph newGraph = graph(newNodes, newEdges);
        for (auto& v : G.nodes) {
            pair<double, node*> vtoAi = Dijkstra(newGraph, v.get(), nv.get());
        }
    }
    preprocess();
}

void preprocess (graph G) {

}

// this is closely related to the orthogonal range problem, and here we use the priority search tree.