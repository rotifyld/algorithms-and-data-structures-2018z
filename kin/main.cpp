#include <iostream>
using namespace std;


const long long trillion = 1000000000;
const int M = 1 << 15;
long long trees[12][2 * M + 5];
int a[M + 5];
long long w[12][M + 5];

long long query(int t, int p, int k) {
    if (p > k) return 0;
    p += M;
    k += M;
    long long w = trees[t][p];
    if (p != k) w += trees[t][k];
    while (p/2 != k/2) {
        if (p % 2 == 0) w += trees[t][p + 1];
        if (k % 2 == 1) w += trees[t][k - 1];
        p /= 2; k /= 2;
        w %= trillion;
    }
    return w;
}

void insert(int t, int x, long long v) {
    x += M;
    trees[t][x] += v;
    do {
        x /= 2;
        trees[t][x] += v;
        trees[t][x] %= trillion;
    } while (x != 1);
}

int main() {
    int N, K;

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int q;
        cin >> q;
        a[i] = q - 1;
    }

    for (int i = 0; i < N; i++) {
        w[1][i] = 1;
    }

    for (int k = 1; k < K; k++) {
        for (int n = 0; n < N; n++) {
            w[k + 1][n] = query(k, a[n] + 1, N - 1);
            insert(k, a[n], w[k][n]);
        }
    }

    long long wyn = 0;

    for (int i = 0; i < N; i++) {
        wyn += w[K][i];
        wyn %= trillion;
    }
    cout << wyn;

    return 0;
}
