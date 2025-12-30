
#include "Graph.h"
#include "Dijkstra.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;



const double INF = numeric_limits<double>::infinity();
// assuming source and target are inside 
pair<double, node*> Dijkstra(graph& G, node* source, node* target) {
    unordered_map<pair<node*, node*>, double, PairHasher> dist;
    dist[pair(source, source)] = 0;
    for (auto& u: *G.nodes) {
        for (auto& v: u->neighbours) {
            dist[pair(u.get(), v->first.get())] = v->second;
            dist[pair(v->first.get(), u.get())] = v->second;
        }
    }
    for (auto& v: *G.nodes) {
        dist[pair(source, v.get())] = INF; 
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
    for (auto& u : curr->neighbours) {
        node* v = u->first.get();
        if (dist[pair(source, curr)] + dist[pair(curr, v)] < dist[pair(source, v)]) {
            dist[pair(source, v)] = dist[pair(source, curr)] + dist[pair(curr, v)];
        }
    }
    predecessor = curr;
   }
   return pair(dist[pair(source, target)], predecessor);
}

// the goal here is to find the cluster vertex using the modified dijkstra from Thorup Zwick
pair<double, node*> ModifiedDijkstra(graph& G, 
    node* source, 
    unordered_map<pair<node*, node*>, double, PairHasher>& dist,
    unordered_map<pair<node*, int>, double, PairHasher>& NodeToSample) {
    dist[pair(source, source)] = 0;
    for (auto& u: *G.nodes) {
        for (auto& v: u->neighbours) {
            dist[pair(u.get(), v->first.get())] = v->second;
            dist[pair(v->first.get(), u.get())] = v->second;
        }
    }
    for (auto& v: *G.nodes) {
        dist[pair(source, v.get())] = INF; 
    }
    priority_queue<node*, vector<node*>, decltype(comp)> pq(comp); 
    pq.push(source);
    node* predecessor;
    while (!pq.empty()) {
    node* curr = pq.top();
    pq.pop();
    for (auto& u : curr->neighbours) {
        node* v = u->first.get();
        if (distance[pair(source, v)] + u.second < NodeToSample[pair(v, v->mark)] 
                && dist[pair(source, curr)] + dist[pair(curr, v)] < dist[pair(source, v)]) {
            dist[pair(source, v)] = dist[pair(source, curr)] + dist[pair(curr, v)];
        }
    }
    predecessor = curr;
    }
   return pair(dist[pair(source, target)], predecessor); 
}
