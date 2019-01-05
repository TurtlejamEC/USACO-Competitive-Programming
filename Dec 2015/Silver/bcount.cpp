#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define v first
#define id second
#define c first
#define fl second

using namespace std;

pair<ll, ll> dfs (int currentVertex, int destination, int flightID,
              vector< vector< pair <int, int> > >& adj, vector<int>& idCost, vector<bool> visited) {
    visited[currentVertex] = true;

    ll ansCost = 0, ansFlight = 0;
    if (currentVertex == destination) return {ansCost, ansFlight};

    ansCost = 1000000001;
    for (pair<int, int> i: adj[currentVertex]) {
        if (!visited[i.id]) {
            pair<ll, ll> possible = dfs(i.v, destination, i.id, adj, idCost, visited);
            if (possible.c < ansCost) {
                ansCost = possible.c;
                ansFlight = possible.fl;
            }
        }
    }

    if (flightID != -1) {
        ansCost += idCost[flightID];
        ansFlight++;
    }

    return {ansCost, ansFlight};
}

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);

    int A, B, N;
    cin >> A >> B >> N;

    vector<int> idCost;

    vector< vector< pair <int, int> > > adj(1000);

    for (int i = 0; i < N; i++) {
        int cost, flights;
        cin >> cost >> flights;

        idCost[i] = cost;

        int previousVertex;
        cin >> previousVertex;

        previousVertex--;
        for (int j = 1; j < flights; j++) {
            int vertex;
            cin >> vertex;
            vertex--;

            adj[previousVertex].emplace_back({vertex, i});

            previousVertex = vertex;
        }
    }

    vector<bool> visited(1000);
    pair<ll, ll> ans = dfs(A, B, -1, adj, idCost, visited);

    cout << ans.c << " " << ans.fl << endl;

    return 0;
}