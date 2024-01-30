#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int binarySearch(const vector<int> &A, int V, bool isDescending) {
  int low = 0, high = A.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (A[mid] == V)
      return mid;
    if (A[mid] < V)
      isDescending ? high = mid - 1 : low = mid + 1;
    else
      isDescending ? low = mid + 1 : high = mid - 1;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  int length = 15;
  bool isDescending = false;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-L") == 0 && i + 1 < argc) {
      length = atoi(argv[i + 1]);
    }
    if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--descending") == 0) {
      isDescending = true;
    }
  }

  vector<int> A(length);
  for (int i = 0; i < length; ++i)
    A[i] = rand() % 1000;

  isDescending ? sort(A.begin(), A.end(), greater<int>())
               : sort(A.begin(), A.end());

  cout << "Sorted array A: ";
  for (int i : A)
    cout << i << " ";

  int V;
  cout << "\nInteger value for V: ";
  cin >> V;

  int result = binarySearch(A, V, isDescending);
  cout << result << endl;

  if (result == -1)
    assert(find(A.begin(), A.end(), V) == A.end());
  else
    assert(A[result] == V);

  cout << "The result is correct" << endl;

  return 0;
}

