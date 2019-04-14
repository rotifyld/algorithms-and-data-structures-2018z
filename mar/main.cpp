#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

using Time = int;
using Depth = int;    // a depth in a G graph, whereas it gives an agility of (1 << agility) width
using Width = int;

struct Edge {
    Depth y;
    Width x;
    Time t;
};

const char Ground = '.';
const char Magic = '*';
const char TeleL = '<';
const char TeleR = '>';
const char Hard = 'U';

int n;
int K;
int U;

const Time INFINITY_TIME = numeric_limits<int>::max();
const Width MAX_X = 100002;
const Depth MAX_Y = 19;         // smallest y : (2^y > MAX_X)
vector<Edge> G[MAX_Y][MAX_X];
char course[MAX_X];
Time min_t[MAX_Y][MAX_X];

inline int get_result() {
    Time absolute_min = INFINITY_TIME;

    for (auto& graph_level : min_t) {
        Time level_min = graph_level[n - 1];
        if (level_min != 0 && level_min < absolute_min) {
            absolute_min = level_min;
        }
    }

    return (absolute_min == INFINITY_TIME) ? -1 : absolute_min;
}

inline void single_step(queue<Edge> &currQ, queue<Edge> &Q, queue<Edge> &QU) {
    Depth u_y = currQ.front().y;
    Width u_x = currQ.front().x;
    Time u_t = currQ.front().t;
    currQ.pop();

    if (min_t[u_y][u_x] < u_t) {
        return;
    }

    for (auto& neighbour : G[u_y][u_x]) {
        Width v_x = neighbour.x;
        Depth v_y = neighbour.y;
        Time time_through_u = u_t + neighbour.t;
        if (min_t[v_y][v_x] > time_through_u) {
            min_t[v_y][v_x] = time_through_u;
            if (neighbour.t == 1) {
                Q.push({v_y, v_x, time_through_u});
            } else {    // neighbour.u_t == 1 + U
                QU.push({v_y, v_x, time_through_u});
            }
        }
    }
}

int search_for_shortest_route() {
    queue<Edge> Q;
    queue<Edge> QU;

    Q.push({1, 0, 0});

    while (true) {  // !Q.empty() && !QU.empty()
        if (!Q.empty()) {
            Time curr_t = Q.front().t;
            size_t repeat = Q.size();
            for (size_t i = 0; i < repeat; i++) {
                single_step(Q, Q, QU);
            }
            if (!QU.empty()) {
                while (QU.front().t == curr_t) {
                    single_step(QU, Q, QU);
                }
            }
        } else {
            if (!QU.empty()) {
                single_step(QU, Q, QU);
            } else {
                break;
            }
        }
    }
    return get_result();
}

void generate_graph(Depth y, Width x) {
    if (min_t[y][x] != 0) return; // not to visit same x twice
    min_t[y][x] = INFINITY_TIME;
    if (x == n - 1) return;     // we're on the last piece

    Depth next_y = y;
    Width next_x = x + 1;
    Time next_t = 1;            // default value
    bool its_a_trap = false;

    switch (course[x + 1]) {
        case Magic:
            if ((1 << y) <= n) {
                next_y += 1;
                break;
            }
        case Ground:            // fall-through
            break;
        case TeleL:
            next_x -= K;
            break;
        case TeleR:
            next_x += K;
            break;
        case Hard:
            next_t += U;
            break;
        default:
            its_a_trap = true;
            break;
    }

    if (!its_a_trap) {
        G[y][x].push_back({next_y, next_x, next_t});
        generate_graph(next_y, next_x);
    }

    int jump = 1 << y;
    if (x + jump >= n) return;

    next_y = y;
    next_x = x + jump;
    next_t = 1;
    its_a_trap = false;

    switch (course[x + jump]) {
        case Ground:
            break;
        case Magic:
            next_y += 1;
            break;
        case TeleL:
            next_x -= K;
            break;
        case TeleR:
            next_x += K;
            break;
        case Hard:
            next_t += U;
            break;
        default:
            its_a_trap = true;
            break; // pole pułłapka - nie tworzymy połączenia
    }

    if (!its_a_trap) {
        G[y][x].push_back({next_y, next_x, next_t});
        generate_graph(next_y, next_x);
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> K >> U;

    if (n == 1) {
        cout << 0;
        return 0;
    }

    for (Width x = 0; x < n; x++) {
        cin >> course[x];
    }

    generate_graph(1, 0);
    cout << search_for_shortest_route();
    return 0;
}

