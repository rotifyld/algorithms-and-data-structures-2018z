#include <iostream>
#include <set>
#include <cassert>

using namespace std;

typedef pair<int, int> range_t;

const int N = 100010;
const int M = 1 << 17;

const range_t empty_far = {0, 0};
const range_t empty_close = {0, N};

const string in = "in";
const string over = "over";
const string none = "none";
const string some = "some";

set<pair<int, int>> ranges[N];
range_t closest[2 * M + 10];
range_t furthest[2 * M + 10];

ostream &operator<<(ostream &os, const range_t &p) {
    os << "<" << p.first << ", " << p.second << ">";
    return os;
}

void insert_closest(int i, range_t close) {
    closest[M + i] = close;
    for (int j = (M + i) / 2; j != 0; j /= 2) {
        if (closest[j].second <= close.second) {
            break;
        } else {
            closest[j] = close;
        }
    }
}

void insert_furthest(int i, range_t far) {
    furthest[M + i] = far;
    for (int j = (M + i) / 2; j != 1; j /= 2) {
        if (furthest[j].second >= far.second) {
            break;
        } else {
            furthest[j] = far;
        }
    }
}

void update_closest(int i, range_t next) {
    closest[M + i] = next;
    int from_left = 1 - i % 2; // 1 - true, 0 - false
    for (int j = (M + i) / 2; j != 0; j /= 2) {
        if (next.second < closest[2 * j + from_left].second) {
            closest[j] = next;
        } else {
            closest[j] = closest[2 * j + from_left];
            next = closest[2 * j + from_left];
        }
        assert(closest[j].second <= closest[2 * j].second);
        assert(closest[j].second <= closest[2 * j + 1].second);
        from_left = 1 - j % 2;
    }
}

void update_furthest(int i, range_t next) {
    furthest[M + i] = next;
    int from_left = 1 - i % 2;
    for (int j = (M + i) / 2; j != 1; j /= 2) {
        if (next.second > furthest[2 * j + from_left].second) {
            furthest[j] = next;
        } else {
            furthest[j] = furthest[2 * j + from_left];
            next = furthest[2 * j + from_left];
        }
        assert(furthest[j].second >= furthest[2 * j].second);
        assert(furthest[j].second >= furthest[2 * j + 1].second);
        from_left = 1 - j % 2;
    }
}

void build_trees() {

    for (int i = 0; i < N - 1; ++i) {
        auto set = ranges[i + 1];
        if (!set.empty()) {
            insert_closest(i, {i + 1, set.begin()->first});
            insert_furthest(i, {i + 1, set.rbegin()->first});
        }
    }
}

range_t query_closest(int p, int k) {
    p += M - 1;
    k += M - 1;
    range_t cp = closest[p];
    range_t ck = closest[k];
    while (k - p > 1) {
        if (p % 2 == 1) p++;
        p /= 2;
        if (k % 2 == 0) k--;
        k /= 2;
        if (closest[p].second < cp.second) cp = closest[p];
        if (closest[k].second < ck.second) ck = closest[k];
    }
    if (p != k && p % 2 == 0) { // początek jest lewym dzieckiem
        p /= 2;
        k /= 2;
        if (closest[p].second < cp.second) cp = closest[p];
        if (closest[k].second < ck.second) ck = closest[k];
    }

    return cp.second < ck.second ? cp : ck;
}

range_t query_furthest(int p, int k) {
    p += M - 1;
    k += M - 1;
    range_t cp = furthest[p];
    range_t ck = furthest[k];
    while (k - p > 1) {
        if (p % 2 == 1) p++;
        p /= 2;
        if (k % 2 == 0) k--;
        k /= 2;
        if (furthest[p].second > cp.second) cp = furthest[p];
        if (furthest[k].second > ck.second) ck = furthest[k];
    }
    if (p != k && p % 2 == 0) { // początek jest lewym dzieckiem
        p /= 2;
        k /= 2;
        if (furthest[p].second > cp.second) cp = furthest[p];
        if (furthest[k].second > ck.second) ck = furthest[k];
    }

    return cp.second > ck.second ? cp : ck;
}

void remove_range(range_t p) {
    auto &set = ranges[p.first];
    if (p.second == set.begin()->first) {
        cout << set.begin()->second << " ";
        set.erase(set.begin());
        // na pewno trzeba usunąć z closest, ale może też z furthest
        if (set.empty()) {
            // też
            update_furthest(p.first - 1, empty_far);
            update_closest(p.first - 1, empty_close);
        } else {
            update_closest(p.first - 1, {p.first, set.begin()->first});
        }
    } else {
        cout << set.rbegin()->second << " ";
        set.erase(--set.end());
        // trzeba usunąć tylko z furthest
        range_t next = (set.empty()) ? empty_far : range_t{p.first, set.rbegin()->first};
        update_furthest(p.first - 1, next);
    }
}

void cout_ranges(int n) {
    for (int i = 1; i <= n; ++i) {
        cout << i << "\t : ";
        for (auto &k : ranges[i]) {
            cout << k/*.first*/ << ", ";
        }
        cout << endl;
    }
}

void cout_trees() {
    for (int i = 0; i <= 17; ++i) {
        for (int j = 1 << i; j < min(1 << (i + 1), (1 << i) + 20); j++) {
            cout << closest[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    for (int i = 0; i <= 17; ++i) {
        for (int j = 1 << i; j < min(1 << (i + 1), (1 << i) + 20); j++) {
            cout << furthest[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void test_queries(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            cout << "query_cls" << range_t{i, j} << " = " << query_closest(i, j) << endl;
        }
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            cout << "query_frth" << range_t{i, j} << " = " << query_furthest(i, j) << endl;
        }
    }
}

int main() {

    fill_n(closest, 2 * M + 10, empty_close);

    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int p, k;
        cin >> p >> k;
        ranges[p].insert({k, i + 1});
    }

    build_trees();


//    cout_ranges(12);
//    cout_trees();

//    remove_range(range_t{8, 16});
//    remove_range(range_t{1, 2});
//    remove_range(range_t{2, 6});

//    cout_ranges(10);
//    cout_trees();

//    test_queries(10);


    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        string t;
        int p, k;
        cin >> t >> p >> k;
        if (t == in) {
            range_t candidate = query_closest(p, k);
            if (candidate.second <= k) {
                remove_range(candidate);
            } else {
                cout << "-1 ";
            }
        } else if (t == over) {
            range_t candidate = query_furthest(1, p);
            if (candidate.second >= k) {
                remove_range(candidate);
            } else {
                cout << "-1 ";
            }
        } else if (t == none) {
            range_t candidate = query_closest(1, p - 1);
            if (candidate.second < p) {
                remove_range(candidate);
            } else {
                candidate = query_closest(k + 1, N - 5);
                if (candidate != empty_close) {
                    remove_range(candidate);
                } else {
                    cout << "-1 ";
                }
            }
        } else {// t == some
            range_t candidate = query_furthest(1, k);
            if (candidate.second >= p) {
                remove_range(candidate);
            } else {
                cout << "-1 ";
            }
        }
    }

//    cout_ranges(10);
//    cout_trees();

    return 0;
}
