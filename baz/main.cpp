#include <iostream>
#include <vector>
using namespace std;

long long result(long long suma, int cena, int wie, int prz, int jed) {
    if (suma % 2 == 1) {
        return suma;
    } else {
        if (!prz) {
            if (!wie || !jed) {
                return -1;
            } else {
                return (suma - wie) + jed;
            }
        } else {
            if (!wie || !jed) {
                return (suma - cena) + prz;
            } else {
                return max((suma - wie) + jed, (suma - cena) + prz);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    // DEKLARACJE, WEJŚCIE

    int n;
    int m;
    cin >> n;

    vector<int> cena(n);
    vector<long long> suf(n); // suma suffiksowa
    vector<int> prz(n); // największa liczba przeciwnej parzystości mniejsza od znajdującej się na tym samym indeksie w tablicy cena[]
    vector<int> jed(n); // największa   ~    jednakowej      ~
    vector<int> wie(n); // najmniejsza  ~    przeciwnej      ~      większa

    for (auto &it : cena) {
        cin >> it;
    }

    cin >> m;
    vector<int> dni(m);

    for (auto &it : dni) {
        cin >> it;
    }

    // PRZETWARZANIE DANYCH

    // stwórz tablicę sufiksów i wypełnij tablicę wie
    int ost = 0;
    suf[n - 1] = cena[n - 1];
    wie[n - 1] = 0;
    ost = 0;
    for (int i = n - 2; i >= 0; --i) {
        suf[i] = suf[i + 1] + cena[i];
        if (cena[i + 1] % 2 == cena[i] % 2) {
            wie[i] = ost;
        } else {
            wie[i] = cena[i + 1];
            ost = cena[i + 1];
        }
    }

    int ni = 0;    // ostatnia nieparzysta
    int pa = 0;    // ostatnia parzysta

    // wypełnij tablice prz[] jed[]
    for (int i = 0; i < n; ++i) {
        if (cena[i] % 2 == 0) {
            prz[i] = ni;
            jed[i] = pa;
            pa = cena[i];
        } else {
            prz[i] = pa;
            jed[i] = ni;
            ni = cena[i];
        }
    }

    // WYJŚCIE

    /*for (int i = 0; i < n; ++i) {
        cout << cena[i] << "\t" << suf[i] << "\t" << prz[i] << "\t"<< jed[i] << "\t" << wie[i] << "\n";
    }*/

    for (int i = 0; i < m; ++i) {
        int k = n - dni[i];
        cout << result(suf[k], cena[k], wie[k], prz[k], jed[k]) << "\n";
    }
}
