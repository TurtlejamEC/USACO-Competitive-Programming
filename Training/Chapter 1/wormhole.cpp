/*
ID: elicho21
LANG: C++
TASK: wormhole
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define x first
#define y second

using namespace std;

/*int factorial (int n) {
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

int triangular (int n) {
    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += i;
    }
    return ans;
}*/

int ans = 0;
int N;

bool traversePairs (vector< pair<int, int> > wormholes, vector< pair<int, int> > pairs, vector<bool> visited,
               int testingI, pair<int, int> testing = {-1, -1}) {

/*    for (int i = 0; i < visited.size(); i++) {
        if (i != testingI) {
            if (testing.x <= wormholes[pairs[i].x].x && testing.y == wormholes[pairs[i].x].y) {
                if (visited[i]) {
                    return true;
                } else {
                    visited[i] = true;
                    return traversePairs(wormholes, pairs, visited, i, {wormholes[pairs[i].y].x, wormholes[pairs[i].y].y});
                }
            } else if (testing.x <= wormholes[pairs[i].y].x && testing.y == wormholes[pairs[i].y].y) {
                if (visited[i]) {
                    return true;
                } else {
                    visited[i] = true;
                    return traversePairs(wormholes, pairs, visited, i, {wormholes[pairs[i].x].x, wormholes[pairs[i].x].y});
                }
            }
        }
    }*/

    pair<int, int> closest = {-1, -1};
    for (int i = 0; i < pairs.size(); i++) {
        /*cout << "Testing: " << testing.x << ", " << testing.y << endl;
        cout << wormholes[pairs[i].x].x << ", " << wormholes[pairs[i].x].y << "||" << wormholes[pairs[i].y].x << ", " << wormholes[pairs[i].y].y << endl;
        cout << pairs[i].y << endl;*/
        if (wormholes[pairs[i].x] != testing) {
            if (wormholes[pairs[i].x].y == testing.y && wormholes[pairs[i].x].x > testing.x) {
                if (closest == make_pair(-1, -1)) {
                    closest = {i, 0};
                } else {
                    if (closest.y == 0) {
                        if (wormholes[pairs[i].x].x < wormholes[pairs[closest.x].x].x) {
                            closest = {i, 0};
                        }
                    } else if (closest.y == 1) {
                        if (wormholes[pairs[i].x].x < wormholes[pairs[closest.x].y].x) {
                            closest = {i, 0};
                        }
                    }
                }
            }
        }

        if (wormholes[pairs[i].y] != testing) {
            if (wormholes[pairs[i].y].y == testing.y && wormholes[pairs[i].y].x > testing.x) {
                if (closest == make_pair(-1, -1)) {
                    closest = {i, 1};
                } else {
                    if (closest.y == 0) {
                        if (wormholes[pairs[i].y].x < wormholes[pairs[closest.x].x].x) {
                            closest = {i, 1};
                        }
                    } else if (closest.y == 1) {
                        if (wormholes[pairs[i].y].x < wormholes[pairs[closest.x].y].x) {
                            closest = {i, 1};
                        }
                    }
                }
            }
        }
    }

    if (closest == make_pair(-1, -1)) {
        return false;

    } else {
//        if (visited[closest.x]) {
//            return true;
//        } else {
//            visited[closest.x] = true;
//        }

        if (closest.y == 0) {
            if (visited[pairs[closest.x].x]) {
                return true;
            } else {
                visited[pairs[closest.x].x] = true;
            }

            return traversePairs(wormholes, pairs, visited, testingI, {wormholes[pairs[closest.x].y].x, wormholes[pairs[closest.x].y].y});
        } else if (closest.y == 1) {
            if (visited[pairs[closest.x].y]) {
                return true;
            } else {
                visited[pairs[closest.x].y] = true;
            }

            return traversePairs(wormholes, pairs, visited, testingI, {wormholes[pairs[closest.x].x].x, wormholes[pairs[closest.x].x].y});
        }

    }

    return false;
}

bool testPairs (vector< pair<int, int> > wormholes, vector< pair<int, int> > pairs) {
    /*for (int i = 0; i < pairs.size(); i++) {
        if (wormholes[pairs[i].x].y == wormholes[pairs[i].y].y) {
            return true;
        }
    }*/

    for (int i = 0; i < pairs.size(); i++) {
        vector<bool> visited(wormholes.size());
        visited[pairs[i].y] = true;
        if (traversePairs(wormholes, pairs, visited, i, wormholes[pairs[i].x])) {
//            cout << pairs[i].x << " -- ";
            return true;
        }
        visited[pairs[i].y] = false;

        visited[pairs[i].x] = true;
        if (traversePairs(wormholes, pairs, visited, i, wormholes[pairs[i].y])) {
//            cout << pairs[i].y << " -- ";
            return true;
        }
        visited[pairs[i].x] = false;
    }

    return false;
}

void pairUp (vector< pair<int, int> > wormholes, vector<bool> available, vector< pair<int, int> > pairs, int pairX = -1) {
    if (pairs.size() == N / 2 && all_of(available.begin(), available.end(), [](bool v) { return !v; })) {
        /*for (pair<int, int> k: pairs) {
            cout << "(" << k.x << ", " << k.y << ") ";
        }
        cout << endl;*/
        if (testPairs(wormholes, pairs)) {
            /*for (pair<int, int> k: pairs) {
                cout << "(" << k.x << ", " << k.y << ") ";
            }
            cout << endl;*/
            ans++;
        }
    } else {
        for (int i = 0; i < wormholes.size(); i++) {
            if (available[i]) {
                available[i] = false;
                if (pairX == -1) {
                    pairUp(wormholes, available, pairs, i);
                } else {
                    pairs.push_back({pairX, i});
                    pairUp(wormholes, available, pairs);
                    pairs.pop_back();
                    available[i] = true;
                }
            }
        }
    }
}

int main() {
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);

    cin >> N;

    vector< pair<int, int> > wormholes(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        wormholes[i] = {x, y};
    }

    pairUp(wormholes, vector<bool>(N, true), vector< pair<int, int> >());
    cout << ans << endl;

    /*int pairs = 0;
    vector<bool> paired(N);
    for (int i = 0; i < N; i++) {
        if (!paired[i]) {
            for (int j = i + 1; j < N; j++) {
                if (!paired[j] && wormholes[i].y == wormholes[j].y) {
                    paired[i] = true;
                    pairs++;
                }
            }
        }
    }

    *//*int count = 0;
    for (int i = 0; i < N; i++) {
        if (paired[i]) count++;
    }*//*


    int ans = 0;
    if (pairs % 2 == 0) {
        ans = pairs * factorial(N - 2) / (factorial((N - 2) / 2) * (int) pow(2, (N - 2) / 2));
    } else {
        ans = triangular(pairs);
    }
    cout << pairs << endl;*/
    return 0;
}