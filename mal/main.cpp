#include <iostream>
#include <set>
using namespace std;

const int infty = 1000005;


int main() {

    set<pair<int, int>> au;
    int white = 0;

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int p, k;
        char c;
        cin >> p >> k >> c;

        set<pair<int, int>>::iterator left, right;

        left = au.upper_bound({p, infty});

        if (left == au.begin()) {
            left = au.insert({p, p}).first;
            white++;
        } else {
            --left;
            if (p <= left->second) {
                // do nothing
            } else {
                left = au.insert({p, p}).first;
                white++;
            }
        }

        if (p == k) {
            right = left;
        } else {
            right = au.upper_bound({k, infty});

            if (right == au.begin()) {
                right = au.insert({k, k}).first;
                white++;
            } else {
                --right;
                if (k <= right->second) {
                    // do nothing
                } else {
                    right = au.insert({k, k}).first;
                    white++;
                }
            }
        }

//        cout << "left = <" << left->first << ", " << left->second << ">\n";
//        cout << "right = <" << right->first << ", " << right->second << ">\n";

        if (c == 'B') {

            p = left->first;
            k = right->second;

            while (left != right) {
                white -= (left->second - left->first + 1);
                left = au.erase(left);
            }
            white -= (left->second - left->first + 1);
            left = au.erase(left);

            au.insert({p, k});
            white += (k - p + 1);

        } else {

            if (p != left->first) {
                left = au.insert({left->first, p - 1}).first;
                white += (left->second - left->first + 1);
                left++;
            }
            if (k != right->second) {
                right = au.insert({k + 1, right->second}).first++;
                white += (right->second - right->first + 1);
                right--;
            }

            while (left != right) {
                white -= (left->second - left->first + 1);
                left = au.erase(left);
            }
            white -= (left->second - left->first + 1);
            left = au.erase(left);

        }

        cout << white << "\n";
    }
}
