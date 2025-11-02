#include <iostream>
#include <vector>

using namespace std;

// group by generator

// in this case, the group element types are arrays of 1 to n, eg [1,3,2] means that the 1st element
// at position 1, 2nd element goes to 3 and 3rd element goes to 1

// numbers are from 0 to n - 1 for simplicity
int* apply(int* perm, int* current, int sz) {
    for (int i = 0; i < sz; i += 1) {
        int pos2 = perm[i];
        int curr = current[i];
        while (pos2 != i) {
            int a = current[pos2];
            current[pos2] = curr; 
            curr = a;
            pos2 = perm[pos2]; 
        }
    }  
    return current;
}

class Group {
    // c++ using
    private: 
    vector<int*> generators;
    int* standard;
    int sz;
    vector<int*>* representative;
    public: 
    Group(vector<int*> generators, int size) {
        for (auto& i : generators) {
            this->generators.push_back(i);
        }
        sz = size;
        int stn[sz];
        for (int i = 0; i < sz; i += 1) {
            stn[i] = i;
        }
        standard = stn;
        vector<int*> table[sz];
        representative = table;
        for (auto &i: this->generators) {
            sift(i);
        }
        // this will cost a lot
        for (int i = 0; i < sz; i += 1) { // sifting each possible pair while updating the array 
            for (int j = 0; j < representative[i].size(); j += 1) {
                int* g = representative[i][j];
                for (int k = 0; k < sz; k += 1) {
                    for (int l = 0; l < representative[k].size(); l += 1) { 
                        // fortunately, we know representative[k].size() will stop at k 
                        int* h = representative[k][l]; 
                        int* gh = apply(g, h);
                        int* hg = apply(h, g);
                        sift(gh);
                        sift(hg);
                    }
                }
            }
        } 
    }
    // multiplication of permutation follows from definition above
    int* multiply(int* a, int* b) {
       return apply(a, apply(b, standard));  
    }

    int* invert(int* x) {
        int inv[sz];
        for (int i = 0; i < sz; i += 1) {
            inv[x[i]] = i;
        }
        return inv;
    }

    int* findy(int* x, int n) {
        // checks on row n, do we have some y such that 
        bool check = false;
        for (int i = 0; i < representative[n].size(); i += 1) {
            int* y = representative[n][i];
            int* yinv_x = apply(invert(y), x);
            int j = 0;
            while (j < n) {
                if (yinv_x[j] != j) {
                    break;
                }
            }
            if (j == n) {
               check = true; 
            }
            if (check) {
                return yinv_x;
            }
        }
        return NULL;
    }

    void sift(int* x) {
        int n = 0;
        int* curr = findy(x, n);
        while(n < sz && curr != NULL) {
            x = curr; 
            n += 1;
            curr = findy(curr, n);
        }
        if (n != sz)  { // a canonical representation was found!
            return;
        } 
        representative[n].push_back(x);
    }

    vector<int*> canonize(int* x) { // very similar to sift;
        vector<int*> ans;
        int n = 0;
        int* curr = findy(x, n);
        while (n < sz && curr != NULL) {
            x = curr;
            n += 1;
            ans.push_back(curr);
            curr = findy(curr, n);
        }
        if (n != 1) {
            cout << "table not complete" << endl;
            return;
        }
    }
};