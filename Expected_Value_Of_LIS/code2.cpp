
#include <algorithm>
#include <cmath>
#include <cstring> // For memset (though better to use vector constructors)
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// The maximum size of the array and the number of trials
const int N_MAX = 10000;
const int N_TRIALS =
    1000; // Reduced trials from 1e4 to 1e3 for speed in environment

void randomize(int *arr, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);

    swap(arr[i], arr[j]);
  }
}

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

double E_LIS(int *arr, int n) {
  vector<int> LIS_results(N_TRIALS);

  for (int i = 0; i < N_TRIALS; i += 1) {
    randomize(arr, n);

    LIS_results[i] = findLIS(arr, n);
  }

  long long sum = 0;
  for (int len : LIS_results) {
    sum += len;
  }

  return (double)sum / N_TRIALS;
}

// --- Main Program ---

int main() {
  srand(time(NULL));

  int arr[N_MAX];
  for (int i = 0; i < N_MAX; i += 1) {
    arr[i] = i;
  }

  double ans = E_LIS(arr, N_MAX);

  cout.precision(4);
  cout << "Expected Value of LIS for N =" << N_MAX << " is: " << fixed << ans << endl;

  return 0;
}
