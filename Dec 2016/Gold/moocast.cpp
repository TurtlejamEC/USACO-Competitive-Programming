#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canReach(pair<int, int> cow1, pair<int, int> cow2, int X) {
    long long squaredDist = (cow1.first - cow2.first) * (cow1.first - cow2.first) +
            (cow1.second - cow2.second) * (cow1.second - cow2.second);
    return squaredDist <= X;
}

void dfs(int current, vector< vector<int> >& graph, vector<bool>& visited) {
    for (int i = 0; i < graph[current].size(); i++) {
        int adjacent = graph[current][i];

        if (visited[adjacent]) continue;

        visited[adjacent] = true;
        dfs(adjacent, graph, visited);
    }
}

int main () {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    int N;
    cin >> N;
    vector< pair<int, int> > locations(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        locations[i] = {x, y};
    }

    int lo = 0, hi = 625000000;
    while (lo < hi) {
        int X = (lo + hi) / 2;

        // Build graph
        vector< vector<int> > connections(N);
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (canReach(locations[i], locations[j], X)) {
                    connections[i].push_back(j);
                    connections[j].push_back(i);
                }
            }
        }

        vector<bool> visited(N);
        visited[0] = true;
        dfs(0, connections, visited);

        bool reachedEveryone = true;
        for (int i = 0; i < visited.size(); i++) {
            if (!visited[i]) {
                reachedEveryone = false;
                break;
            }
        }

        if (reachedEveryone) {
            hi = X;
        } else {
            lo = X + 1;
        }
    }

    cout << lo << endl;

    return 0;
}