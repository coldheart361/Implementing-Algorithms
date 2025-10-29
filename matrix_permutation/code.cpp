#include <iostream>
#include <vector>
using namespace std;

const int N_MAX = 250;

// I need to randomly permute elements of a matrix

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) {
    return a.first < b.first;
  }
  return a.second < b.second;
}

// --- Segment Tree Implementation ---

void buildTree(vector<int> &tree, int pos, int low, int high, int index,
               int value) {
  if (low == high) {
    tree[pos] = value;
    return;
  }

  int mid = low + (high - low) / 2;

  if (index <= mid) {
    buildTree(tree, 2 * pos + 1, low, mid, index, value);
  } else {
    buildTree(tree, 2 * pos + 2, mid + 1, high, index, value);
  }

  tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]);
}

int findMax(const vector<int> &tree, int pos, int low, int high, int start,
            int end) {
  if (high < start || low > end) {
    return 0;
  }

  if (low >= start && high <= end) {
    return tree[pos];
  }

  int mid = low + (high - low) / 2;

  int left_max = findMax(tree, 2 * pos + 1, low, mid, start, end);
  int right_max = findMax(tree, 2 * pos + 2, mid + 1, high, start, end);

  return max(left_max, right_max);
}

// find LIS 
int findLIS(int arr[], int n) {
  if (n == 0)
    return 0;

  vector<pair<int, int>> p(n);
  for (int i = 0; i < n; i += 1) {
    p[i].first = arr[i];
    p[i].second = i;
  }
  sort(p.begin(), p.end(), cmp);

  int tree_size = 4 * n + 1;
  vector<int> tree(tree_size, 0);

  int max_lis_len = 0;

  for (int i = 0; i < n; i += 1) {
    int original_index = p[i].second;

    int prev_lis = 0;
    if (original_index > 0) {
      prev_lis = findMax(tree, 0, 0, n - 1, 0, original_index - 1);
    }

    int current_lis = prev_lis + 1;

    buildTree(tree, 0, 0, n - 1, original_index, current_lis);

    max_lis_len = max(max_lis_len, current_lis);
  }

  return max_lis_len;
}

void randomize(int *arr, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swap(arr[i], arr[j]);
  }
}

void randomize_Matrix(int arr[][N_MAX], int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);

    for (int l = 0; l < n; l += 1) {
        swap(arr[l][i], arr[l][j]);
    }
  }
}

int findMaxLIS(int arr[][N_MAX], int n) {
    int ans = 0;
    for (int i = 0; i < n; i += 1) {
        ans = max(ans, findLIS(arr[i], n));
    }
    return ans;
}

// I suppose we are also interested in finding the success rate hahaha
double test(int arr[][N_MAX], int n) {
    int ans = 0;
    int trials = n * n;
    for (int i = 0; i < n; i += 1) {
        randomize_Matrix(arr, n);
        if (findMaxLIS(arr, n) <= 2 * sqrt(n)) {
            ans += 1;
        }
    }
    return (double) ans / trials;
}

int main() {
    srand(time(NULL));
    int arr[N_MAX][N_MAX];
    for (int i = 0; i < N_MAX; i += 1) {
        for (int j = 0; j < N_MAX; j += 1) {
            arr[i][j] = i * N_MAX + j;
        }
        randomize(arr[i], N_MAX);
    }
    cout << test(arr, N_MAX) << endl;
}