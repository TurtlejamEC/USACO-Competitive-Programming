#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

int dfs(int current, int previous, vector< vector<int> >& graph, vector<int>& type, vector<bool>& visited) {
    int childType = 1;
    int ans = type[current];
    visited[current] = true;

    set<int> justUsed;
    for (int i: graph[current]) {
        if (visited[i]) continue;

        while (childType == type[current] || childType == type[previous] || (justUsed.find(childType) != justUsed.end())) {
            childType++;
        }

        type[i] = childType;
        justUsed.insert(childType);

        ans = max(ans, dfs(i, current, graph, type, visited));
    }

    return ans;
}

int main() {
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);

    int N;
    cin >> N;

    vector< vector<int> > graph(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    vector<bool> visited(N + 1);
    vector<int> type(N + 1);

    type[1] = 1;
    cout << dfs(1, 1, graph, type, visited) << endl;
    return 0;
}