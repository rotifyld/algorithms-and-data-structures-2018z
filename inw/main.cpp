#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  vector<int> v;
  int n;
  int max = 0;

  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    if (a > max) max = a;
    if (max == i) v.push_back(max);
  }

  cout << v.size() << "\n";

  int prev = 0;
  for (auto& a : v) {
    cout << a - prev;
    for (int i = prev + 1; i <= a; i++) cout << " " << i;
    cout << "\n";
    prev = a;
  }

  return 0;
}
