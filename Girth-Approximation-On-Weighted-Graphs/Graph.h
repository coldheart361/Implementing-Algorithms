#include <vector>
using namespace std;

double tolerance = nice_power(1/10, 8);

double absolute_diff(double a, double b) {
    if (a - b < 0) {
        return b - a;
    } else {
        return a - b;
    }
}

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

double kth_root(double x, int k) {
    double guess1 = 1;
    while (absolute_diff(guess1, x) > nice_power(1/10, 8)) {
        guess1 = ((k-1) * nice_power(guess1, k) + x) / (k * nice_power(guess1, k-1));
    }
    return guess1;
}

class node {
    public : 
    int mark;
    vector<pair<shared_ptr<node>, double>*> neighbours;
    node(vector<pair<shared_ptr<node>, double>*>& neighbours) {
        this->neighbours = neighbours;
    }
};

// should we always follow the unique_ptr   
class graph {
    public :
    vector<shared_ptr<node>>* nodes;
    int sz;
    graph(vector<shared_ptr<node>>& nodes) {
        this->nodes = &nodes;
    }
};
