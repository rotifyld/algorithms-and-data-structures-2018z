#include <iostream>
using namespace std;

const int end_char = '\n';

int main() {



    int n = 1;          // wczytanych znaków łącznie
    int o = 0;          // ostatnia wczytana litera
    int m = 1000002;    // minimalna odległość między dwoma różnymi literami

    int c;

    for (c = getchar(); c == '*'; c = getchar()) {
        n++;
    }

    if (c == end_char) {
        cout << 1;
        return 0;
    }

    o = c;
    int i = 0;          // odległość od ostatniej wczytanej litery

    for (c = getchar(); c != end_char; c = getchar()) {
        n++;
        if (c == '*') {
            i++;
        } else {
            if (o == c) {
                i = 0;
            } else {
                m = min(m, i);
                i = 0;
                o = c;
            }
        }
    }

    if (n < m) {
        cout << 1;
    } else {
        cout << n - m;
    }

    return 0;
}
