#include <iostream>
#include <queue>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;
using Node = pair<int, int>;

const int N = 500010;
const int LOG_N = 23;
int p[N];
int l[N];
int r[N];
int d[N];
int links[N][LOG_N];
Node f[N];
Node fup[N];
Node fdown[N];

int n;

Node operator+(const Node &l, const Node &r) {
    return {l.first + r.first, l.second + r.second};
}

ostream &operator<<(ostream & os, const Node & n) {
    os << "<" << n.first << ", " << n.second << ">";
    return os;
}

void find_depth() {
    queue<int> q;
    q.push(1);
    d[1] = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (l[curr] != -1) {
            d[l[curr]] = d[curr] + 1;
            q.push(l[curr]);
        }
        if (r[curr] != -1) {
            d[r[curr]] = d[curr] + 1;
            q.push(r[curr]);
        }
    }
}

void find_links() {
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        int now = curr;
        if (p[curr] != -1) {
            links[curr][0] = p[curr];
            now = p[curr];

            for (int i = 1; links[now][i - 1] != 0; i++) {
                now = links[now][i - 1];
                links[curr][i] = now;
            }
        }

        if (l[curr] != -1) q.push(l[curr]);
        if (r[curr] != -1) q.push(r[curr]);

    }
}

int ancestor(int v, int h) {
    for (int i = 0; h != 0; i++) {
        if (h % 2 == 1) {
            v = links[v][i];
        }
        h >>= 1;
    }
    return v;
}

int find_lca(int u, int v) {
    int dv = d[v];
    int du = d[u];
    if (dv < du) {
        u = ancestor(u, du - dv);
    } else if (du < dv) {
        v = ancestor(v, dv - du);
    }

    if (u == v) return u;

    for (int i = static_cast<int>(log2(n)); i >= 0; i--) {
        if (links[u][i] != links[v][i]) {
            v = links[v][i];
            u = links[u][i];
        }
    }
    return p[u];
}

Node fardown(int u) {

    if (fdown[u].second != 0) return fdown[u];

    Node c_1 = {0, u};
    Node c_2 = (l[u] != -1) ? fardown(l[u]) + Node{1, 0} : Node{-1, 0};
    Node c_3 = (r[u] != -1) ? fardown(r[u]) + Node{1, 0} : Node{-1, 0};

    return fdown[u] = c_1 < c_2 ? c_2 < c_3 ? c_3 : c_2 : c_1 < c_3 ? c_3 : c_1;
}

Node farup(int u) {

    if (fup[u].second != 0) return fup[u];

    Node c_1 = {0, u};
    Node c_2 = (p[u] != -1) ? farup(p[u]) + Node{1, 0} : Node{-1, 0};
    Node c_3 = (p[u] != -1 && l[p[u]] != -1 && r[p[u]] != -1) ? (l[p[u]] == u) ? fardown(r[p[u]]) + Node{2, 0} : fardown(l[p[u]]) + Node{2, 0} : Node{-1, 0};

    return fup[u] = c_1 < c_2 ? c_2 < c_3 ? c_3 : c_2 : c_1 < c_3 ? c_3 : c_1;
}

Node find_furthest(int u) {

    if (f[u].second != 0) return f[u];

    auto c_1 = fardown(u);
    auto c_2 = farup(u);

    return f[u] = (c_1 < c_2) ? c_2 : c_1;
}

int find_in_distance(int u, int dist) {
    Node furthest = find_furthest(u);
    int d_max = furthest.first;
    int v = furthest.second;
    if (d_max < dist) {
        return -1;
    }

    int l = find_lca(u, v);
    return (dist <= d[u] - d[l]) ? ancestor(u, dist) : ancestor(v, d_max - dist);
}

void cout_everything() {
    for (int i = 1; i <= n; i++) {
        cout << i << ":\tp = " << p[i] << "\tl = " << l[i] << "\tr = " << r[i] << "\td = " << d[i]
             << "\tf = " << find_furthest(i) << "\n";
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < log(n); ++j) {
            cout << links[i][j] << "\t";
        }
        cout << "\n";
    }


    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << find_lca(i, j) << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        if (l[i] != -1) p[l[i]] = i;
        if (r[i] != -1) p[r[i]] = i;
    }
    p[1] = -1;

    find_depth();

    find_links();

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, d;
        cin >> u >> d;
        cout << find_in_distance(u, d) << "\n";
    }

//    cout_everything();

    return 0;
}