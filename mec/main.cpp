#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<bitset<64>> v;
  for (int i = 0; i < n; i++) {
    bitset<64> h;
    v.push_back(h);
  }

  int g;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n / 2; j++) {
      cin >> g;
      v[g - 1].set(i);
    }
    for (int j = 0; j < n / 2; j++) {
      cin >> g;
    }
  }

  sort(v.begin(), v.end(), [](bitset<64> a, bitset<64> b) {
    return a.to_ullong() < b.to_ullong();
  });

  if (v.end() == unique(v.begin(), v.end())) {
    cout << "TAK";
  } else {
    cout << "NIE";
  }



  return 0;
}

