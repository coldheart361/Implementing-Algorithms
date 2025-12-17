#include <vector>
using namespace std;

double tolerance = nice_power(1/10, 8);

double nice_power(double x, int y) {
    if (y == 0) {
        return 1;
    } else {
        double xy = nice_power(x, y/2);
        if (y % 2 == 0) {
            return xy * xy;
        } else {
            return xy * xy * x;
        }
    }
}

double kth_root(double n) {
    
}

class node {
    public : 
    graph G;
    vector<edge> edges;
};

class edge {
    public :
    pair<node, node> vertices;
    double len;
};

class graph {
    public :
    vector<node> nodes;
    vector<edge> edges;
    int sz;
};

graph sample(graph G, int k) {
   srand(1); 
   float r = rand();
   if (r < ) {

   }
}