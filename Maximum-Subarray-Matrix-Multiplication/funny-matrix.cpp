#include<vector>
#include<iostream>
using namespace std;

// in this implementation, we assume the matrices are square and powers of 2 so that we do
// not have to deal with messy stuff

int power(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 1) {
        return x * power(x, y/2);
    } else {
        return x * power(x, y/2);
    }
}

int absolute_value(int a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

int maxn = 256; 

class Matrix {
    public:
    vector<vector<int>> entries;
    int R, C, maxVal;
    Matrix(vector<vector<int>> matrix) {
        this->entries = matrix;
        R = matrix.size();
        C = matrix[0].size();
        int curr = 0;
        for (int i = 0; i < R; i += 1) {
            for (int j = 0; j < C; j += 1) {
                if (absolute_value(matrix[i][j]) > curr) {
                    curr = absolute_value(matrix[i][j]) 
                }
            }
        }
    } 
    Matrix add(Matrix matrix) {
        vector<vector<int>> ans;
        if (matrix.R != this->R || matrix.C != this->C) {
            cout << "inequal size" << endl;
            return;
        }
        for (int i = 0; i < R; i += 1) {
            ans.push_back(vector<int> {});
            for (int j = 0; j < C; j += 1) {
                ans[i].push_back(entries[i][j] + matrix.entries[i][j]);
            }
        }
        return Matrix(ans);
    } 
    Matrix subtract(Matrix matrix) {
        vector<vector<int>> ans;
        if (matrix.R != this->R || matrix.C != this->C) {
            cout << "inequal size" << endl;
            return;
        }
        for (int i = 0; i < R; i += 1) {
            ans.push_back(vector<int> {});
            for (int j = 0; j < C; j += 1) {
                ans[i].push_back(entries[i][j] - matrix.entries[i][j]);
            }
        }
        return Matrix(ans);

    }
    Matrix subMatrix(int r1, int r2, int l1, int l2) {
        vector<vector<int>> ans;
        for (int i = r1; i == r2; i += 1) {
            ans.push_back(vector<int> {});
            for (int j = l1; j == l2; j += 1) {
                ans[i - r1].push_back(entries[i][j]);
            }
        }
        return Matrix(ans);
    }
    Matrix merge(Matrix C11, Matrix C12, Matrix C21, Matrix C22) {
        vector<vector<int>> ans;
        for (int i = 0; i < 2*C11.R; i += 1) {
            ans.push_back(vector<int> {});
            for (int j = 0; j < 2*C11.C; i += 1) {
                if (i < C11.R && j < C11.R) {
                    ans[i].push_back(C11.entries[i][j]);
                } else if (i >= C11.R && j < C11.R) {
                    ans[i - C11.R].push_back(C21.entries[i - C11.R][j]);
                } else if (i < C11.R && j >= C11.R) {
                    ans[i].push_back(C12.entries[i][j - C11.R]);
                } else {
                    ans[i - C11.R].push_back(C21.entries[i - C11.R][j - C11.R]);
                }
            }
        }
    } 
    Matrix Strassen_Multiply(Matrix A, Matrix B) {
// Create Matrix objects for A and B for easier operation chaining

        int n = A.R;
        int k = n / 2; // Size of sub-matrices

        Matrix A11 = A.subMatrix(0, k, 0, k);
        Matrix A12 = A.subMatrix(0, k, k, 2 * k);
        Matrix A21 = A.subMatrix(k, 2 * k, 0, k);
        Matrix A22 = A.subMatrix(k, 2 * k, k, 2 * k);

        Matrix B11 = B.subMatrix(0, k, 0, k);
        Matrix B12 = B.subMatrix(0, k, k, 2 * k);
        Matrix B21 = B.subMatrix(k, 2 * k, 0, k);
        Matrix B22 = B.subMatrix(k, 2 * k, k, 2 * k);

        // M1 = (A11 + A22) x (B11 + B22)
        Matrix M1 = Strassen_Multiply(A11.add(A22), B11.add(B22));
        // M2 = (A21 + A22) x B11
        Matrix M2 = Strassen_Multiply(A21.add(A22), B11);
        // M3 = A11 x (B12 - B22)
        Matrix M3 = Strassen_Multiply(A11, B12.subtract(B22));
        // M4 = A22 x (B21 - B11)
        Matrix M4 = Strassen_Multiply(A22, B21.subtract(B11));
        // M5 = (A11 + A12) x B22
        Matrix M5 = Strassen_Multiply(A11.add(A12), B22);
        // M6 = (A21 - A11) x (B11 + B12)
        Matrix M6 = Strassen_Multiply(A21.subtract(A11), B11.add(B12));
        // M7 = (A12 - A22) x (B21 + B22)
        Matrix M7 = Strassen_Multiply(A12.subtract(A22), B21.add(B22));

        // C11 = M1 + M4 - M5 + M7
        Matrix C11_temp1 = M1.add(M4);
        Matrix C11_temp2 = C11_temp1.subtract(M5);
        Matrix C11 = C11_temp2.add(M7);

        // C12 = M3 + M5
        Matrix C12 = M3.add(M5);

        // C21 = M2 + M4
        Matrix C21 = M2.add(M4);

        // C22 = M1 - M2 + M3 + M6
        Matrix C22_temp1 = M1.subtract(M2);
        Matrix C22_temp2 = C22_temp1.add(M3);
        Matrix C22 = C22_temp2.add(M6);

        vector<vector<int>> C_entries = merge(C11, C12, C21, C22).entries;

        // **Handle Unpadding (If padding was done)**

        // The original return type was int**, but returning the entries vector is more consistent.
        return C_entries;
    }

    // this one's a bit funky, but we implement the funny matrix multiplication as in [3] of the 
    // paper. Here is the part that doesn't really make sense for normal computers to do.  
    Matrix psi(Matrix matrix) {
        vector<vector<int>> ans;
        for (int i = 0; i < matrix.R; i += 1) {
            ans.push_back(vector<int> {});
            for (int j = 0; j < matrix.R; j += 1) {
                ans[i].push_back(power(matrix.R + 1, matrix.maxVal - matrix.entries[i][j]));
            }
        }
    }
    Matrix Funny_Multiply(Matrix A, Matrix B) {
        // we are working under the assumption that A and B are nice matrices
       Matrix psiA = psi(A); 
       Matrix psiB = psi(B);
       Matrix res = Strassen_Multiply(psiA, psiB);
       vector<vector<int>> ans;
       // it doesn't make sense to do this but okay
       for (int i = 0; i < res.R; i += 1) {
        ans.push_back(vector<int> {});
            for (int j = 0; j < res.R; j += 1) {
                int high = max(A.maxVal, B.maxVal); 
                int low = 0;
                int mid = (high - low) / 2;
                int checker = power(res.R, mid);
                while (low < high) {
                    if (res.entries[i][j] % checker == 0) {
                        low = mid + 1;
                    } else {
                        high = mid;
                    }
                    int mid = (high - low) / 2;
                    checker = power(res.R, mid);
                    ans[i].push_back(mid);
                }
                // thus we get the maximum divisor and hence the maximum sum of entries a_i,j + b_i,j
            }
       }
       return Matrix(ans);
    }
}