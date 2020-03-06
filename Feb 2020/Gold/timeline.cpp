#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs (int current, vector< vector< pair<int, int> > >& dependencies, vector<int>& processingOrder,
          vector<bool>& visited) {
    visited[current] = true;
    for (auto p: dependencies[current]) {
        if (!visited[p.first]) {
            dfs(p.first, dependencies, processingOrder, visited);
        }
    }

    processingOrder.push_back(current);
}

int main () {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);

    int N, M, C;
    cin >> N >> M >> C;

    vector<int> ans(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> ans[i];
    }

    // adj graph from session a to b "weighted" by x in triple
    vector< vector< pair<int, int> > > toDoBefore(N+1);
    vector< vector< pair<int, int> > > dependencies(N+1);
    for (int i = 0; i < C; i++) {
        int a, b, x;
        cin >> a >> b >> x;

        dependencies[a].push_back({b, x});
        toDoBefore[b].push_back({a, x});
    }

    vector<int> processingOrder;
    vector<bool> visited(N+1);

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            dfs(i, dependencies, processingOrder, visited);
        }
    }

    reverse(processingOrder.begin(), processingOrder.end());

    for (int i: processingOrder) {
        for (auto p: toDoBefore[i]) {
            ans[i] = max(ans[i], ans[p.first] + p.second);
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}