#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

int main() {
    ios_base::sync_with_stdio(false);

    int w[N];
    int outdeg[N];

    for (int i = 1; i <= N; i++) {
        outdeg[i] = 0;
    }

    vector<vector<int>> dep(N, std::vector<int>{});

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        dep[b].push_back(a);
        outdeg[a]++;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;

    for (int i = 1; i <= n; ++i) {
        if (outdeg[i] == 0) {
            Q.emplace(w[i], i);
        }
    }

    int wynik = 0;

    for (int i = 0; i < k; ++i) {
        int x = Q.top().second;
        Q.pop();

        if (wynik < w[x]) wynik = w[x];

        for (auto& u : dep.at(x)) {
            outdeg[u]--;
            if (outdeg[u] == 0) {
                Q.emplace(w[u], u);
            }
        }
    }

    cout << wynik;
}
