#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 200005;
const int X = 1000000000;

pair<int, int> v[N];
vector<int> e[N];

void wypisz_wymaluj(const vector<pair<int, pair<int, int>>> &wyspy) {
    for (auto &wyspa : wyspy) {
        cout << wyspa.first << ": <" << wyspa.second.first << ", " << wyspa.second.second << ">\n";
    }
    cout << endl;
}

void wymaluj_wypisz(int n) {
    for (int i = 0; i < n; ++i) {
        cout << i << ": ( ";
        for (auto & w : e[i]) {
            cout << w << " ";
        }
        cout << ")\n";
    } cout <<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    vector<pair<int, pair<int, int>>> wyspy;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
        wyspy.emplace_back(i, pair<int, int>{x, y});
    }

    sort(wyspy.begin(), wyspy.end(),
         [](const pair<int, pair<int, int>> &isle1, const pair<int, pair<int, int>> &isle2) {
             return isle1.second.first < isle2.second.first;
         });

    e[wyspy[0].first].push_back(wyspy[1].first);
    for (int i = 1; i < n - 1; ++i) {
        e[wyspy[i].first].push_back(wyspy[i - 1].first);
        e[wyspy[i].first].push_back(wyspy[i + 1].first);
    }
    e[wyspy[n - 1].first].push_back(wyspy[n - 2].first);

//    wypisz_wymaluj(wyspy);
//    wymaluj_wypisz(n);

    sort(wyspy.begin(), wyspy.end(),
         [](const pair<int, pair<int, int>> &isle1, const pair<int, pair<int, int>> &isle2) {
             return isle1.second.second < isle2.second.second;
         });

    e[wyspy[0].first].push_back(wyspy[1].first);
    for (int i = 1; i < n - 1; ++i) {
        e[wyspy[i].first].push_back(wyspy[i - 1].first);
        e[wyspy[i].first].push_back(wyspy[i + 1].first);
    }
    e[wyspy[n - 1].first].push_back(wyspy[n - 2].first);

//    wypisz_wymaluj(wyspy);
//    wymaluj_wypisz(n);

    int min_t[N];
    for (int i = 1; i < n; ++i) {
        min_t[i] = X + 10;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 0});



    while(!q.empty()) {
        int t = q.top().first;
        int w = q.top().second;
        q.pop();

        if (min_t[w] < t) {
            continue;
        }

        for (auto & neigh : e[w]) {
            int t_throu = t + min(abs(v[w].first - v[neigh].first), abs(v[w].second - v[neigh].second));
            if (t_throu < min_t[neigh]) {
                min_t[neigh] = t_throu;
                q.push({t_throu, neigh});
            }
        }
    }

    cout << min_t[n -1];
}