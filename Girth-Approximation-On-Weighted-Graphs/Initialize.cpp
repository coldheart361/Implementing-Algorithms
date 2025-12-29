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

vector<shared_ptr<node>>* sample(vector<shared_ptr<node>>& nodes, int k) {
   srand(1); 
   double probability = kth_root(nodes.size(), k);
   vector<shared_ptr<node>>* result;
   for (auto v : nodes) {
    float r = rand();
    if (r > probability) {
        result->push_back(v);
    }
   }
   return result;
}

void initialize (graph& G, int k) {
    // for the Ai, we also need to store which Ai each v lies in to build the cluster
    vector<vector<shared_ptr<node>>*> A; 
    A.push_back(G.nodes);
    for (int i = 1; i == k - 1; i += 1) {
        A.push_back(sample(*A[i - 1], k));
        int curr = 0; // to check which ones have not been chosen 
        for (auto& sampled : *A[A.size() - 2]) {
            if (sampled != (*A[A.size() - 1])[curr]) {
                sampled.get()->mark = i - 1;
            }
        }
    }
    // to store the distances
    unordered_map<pair<node*, node*>, double, PairHasher> d;
    // to store the previous node 
    unordered_map<pair<node*, node*>, node, PairHasher> pi;
    // to store the distance between node and their mark + 1 sample
    unordered_map<pair<node*, int>, pair<double, node*>, PairHasher> NodeToSample;
    for (int i = 1; i == k - 1; i += 1) {
        vector<pair<shared_ptr<node>, double>*> neighbours;
        shared_ptr<node> nv = make_shared<node>(node(neighbours));
        for (shared_ptr<node> v : *A[i]) {
            neighbours.push_back(&pair(v, 0.0));
            v.get()->neighbours.push_back(&pair(nv, 0.0));
        }
        // don't create new graph, I just realized that storign information about edge is redundant
            G.nodes->push_back(nv);
        for (auto& v : *G.nodes) {
            pair<double, node*> vtoAi = Dijkstra(G, v.get(), nv.get());
            d[pair(v.get(), vtoAi.second)] = vtoAi.first;
            NodeToSample[pair(v.get(), i)] = vtoAi;
        }
        // clean up the G so I can reuse it. 
        for (auto& v : G.nodes->at(G.nodes->size() - 1)->neighbours) {
            v->first.get()->neighbours.pop_back();
        }
        G.nodes->pop_back();

    }
    preprocess(G, A, d);
}

// here, 
void preprocess (graph& G, 
    vector<vector<shared_ptr<node>>*>& A, 
    unordered_map<pair<node*, node*>, double, PairHasher>& d) {
    
}

// this is closely related to the orthogonal range problem, and here we use the priority search tree.