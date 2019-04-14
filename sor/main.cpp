#include <iostream>

using namespace std;

using ll = long long;

const ll mod = 1000000000;
const int M = 1002;

int a[M];
ll tab[M][M][2];
const int Left = 0;
const int Right = 1;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int start = 0; start < n; start++) {
        tab[start][0][Left] = 1;
    }
    for (int len = 1; len < n; len++) {
        for (int start = 0; start < n - len; start++) {

            if (a[start + len - 1] < a[start + len]) {
                tab[start][len][Right] += tab[start][len - 1][Right] % mod;
            }
            if (a[start] < a[start + len]) {
                tab[start][len][Right] += tab[start][len - 1][Left] % mod;
            }
            if (a[start + 1] > a[start]) {
                tab[start][len][Left] += tab[start + 1][len - 1][Left] % mod;
            }
            if (a[start + len] > a[start]) {
                tab[start][len][Left] += tab[start + 1][len - 1][Right] % mod;
            }
        }
    }

    ll wyn = (tab[0][n - 1][Left] + tab[0][n - 1][Right]) % mod;
    cout << wyn;
}
