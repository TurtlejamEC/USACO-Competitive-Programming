#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void buildGraph (int N, vector< vector<int> >& graph) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int vertex = N * i + j;

            if (i + 1 != N) {
                graph[vertex].push_back(vertex + N);
            }

            if (j + 1 != N) {
                graph[vertex].push_back(vertex + 1);
            }

            if (i - 1 != -1) {
                graph[vertex].push_back(vertex - N);
            }

            if (j - 1 != -1) {
                graph[vertex].push_back(vertex - 1);
            }
        }
    }
}

pair<int, int> bfs(int vertex, vector< vector<int> >& graph, vector<char>& config, vector<bool>& visited) {
    int area = 0, perimeter = 0;

    queue<int> next;
    next.push(vertex);
    visited[vertex] = true;

    while (!next.empty()) {
        int current = next.front();
        next.pop();
        area++;

        perimeter += 4 - graph[current].size();
        for (int i: graph[current]) {
            if (visited[i]) continue;
            if (config[i] == '.') {
                perimeter++;
                continue;
            }

            next.push(i);
            visited[i] = true;
        }
    }

    return {area, perimeter};
}

int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    int N;
    cin >> N;

    vector<char> config(N * N);

    string line;
    getline(cin, line);
    for (int i = N - 1; i >= 0; i--) {
        getline(cin, line);

        for (int j = 0; j < N; j++) {
            config[i * N + j] = line[j];
        }
    }

    vector< vector<int> > graph(N*N);
    buildGraph(N, graph);

    vector<bool> visited(N*N);
    int maxArea = 0, minPerimeter = 0;
    for (int i = 0; i < N * N; i++) {
        if (visited[i] || config[i] == '.') continue;
        else {
            pair<int, int> possible = bfs(i, graph, config, visited);

            if (possible.first > maxArea) {
                maxArea = possible.first;
                minPerimeter = possible.second;
            } else if (possible.first == maxArea) {
                minPerimeter = min(possible.second, minPerimeter);
            }
        }
    }

    cout << maxArea << " " << minPerimeter << endl;

    return 0;
}