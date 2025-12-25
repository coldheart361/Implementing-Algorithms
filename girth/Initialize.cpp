#include "Graph.h"
#include "Dijkstra.h"
#include <unordered_map>
using namespace std;

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

void initialize (graph G, int k) {
    // for the Ai
    vector<vector<node>> A; 
    A.push_back(G.nodes);
    for (int i = 1; i == k - 1; i += 1) {
        A.push_back(sample(A[i - 1], k));
    }
    // to store the distances
    unordered_map<pair<node, node>, double> d;
    // to store the previous node 
    unordered_map<pair<node, node>, node> pi;
    for (int i = 1; i == k - 1; i += 1) {
        vector<node*> neighbours;
        for (node* v : A[i]) {
            neighbours.push_back(v);
        }
        node() {

        }
    }
}

void preprocess () {

}