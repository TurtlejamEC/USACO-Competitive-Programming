#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void searchForNew (int room, vector< vector<int> >& switches, vector<bool>& on, vector<bool>& switched,
                   vector< vector<int> >& graph, vector<bool>& visited, queue<int>& nowOn) {
    visited[room] = true;

    if (!switched[room]) {
        nowOn.push(room);
    }

    for (int i: graph[room]) {
        if (on[i] && !visited[i]) searchForNew(i, switches, on, switched, graph, visited, nowOn);
    }
}

int main() {
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    int N, M;
    cin >> N >> M;

    vector< vector<int> > switches((unsigned long)N*N);
    vector<bool> on ((unsigned long)N*N);
    vector<bool> switched((unsigned long)N*N);

    vector< vector<int> > graph((unsigned long)N*N);

    queue<int> nowOn;

    for (int i = 0; i < M; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        int rThis = (y - 1) * N + (x - 1);
        int rSwitch = (b - 1) * N + (a - 1);

        switches[rThis].push_back(rSwitch);
    }

    for (int i = 0; i < N*N; i++) {
        if (i < N*N - N) {
            graph[i].push_back(i + N);
        }
        if (i % N < N - 1) {
            graph[i].push_back(i + 1);
        }
        if (i > N - 1) {
            graph[i].push_back(i - N);
        }
        if (i % N > 0) {
            graph[i].push_back(i - 1);
        }
    }
    on[0] = true;
    nowOn.push(0);

    while (!nowOn.empty()) {

        while (!nowOn.empty()) {
            int currentRoom = nowOn.front();
            nowOn.pop();

            for (int i: switches[currentRoom]) {
                on[i] = true;
            }

            switched[currentRoom] = true;
        }

        vector<bool> visited((unsigned long) N*N);
        searchForNew(0, switches, on, switched, graph, visited, nowOn);
    }

    int ans = 0;
    for (bool i: on) {
        if (i) ans++;
    }

    cout << ans << endl;


    return 0;
}