#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int encrypt (pair<int, int> coord) {
    return 10 * coord.second + coord.first;
}

pair<int, int> decrypt (int vertex) {
    return {vertex % 10, vertex / 10};
}

void buildGraph(int n, vector< vector<int> >& graph) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            int vertex = encrypt({j, i});

            // Up
            if (i + 1 != n) {
                graph[vertex].push_back(vertex + 10);
            }

            // Right
            if (j + 1 != 10) {
                graph[vertex].push_back(vertex + 1);
            }

            // Down
            if (i - 1 != -1) {
                graph[vertex].push_back(vertex - 10);
            }

            // Left
            if (j - 1 != -1) {
                graph[vertex].push_back(vertex - 1);
            }
        }
    }
}

int getColor (int vertex, vector< vector<int> >& grid) {
    int x = decrypt(vertex).first, y = decrypt(vertex).second;
    return grid[x][y];
}

void bfs (int k, int source, vector<bool>& visited, vector< vector<int> >& graph, vector< vector<int> >& grid) {
    vector<int> region;

    queue<int> next;
    next.push(source);
    visited[source] = true;

    int color = getColor(source, grid);

    while (!next.empty()) {
        int vertex = next.front();
        next.pop();

        region.push_back(vertex);

        for (int i: graph[vertex]) {
            if (!visited[i] && color == getColor(i, grid)) {
                next.push(i);
                visited[i] = true;
            }
        }
    }

    if (region.size() >= k) {
        for (int i: region) {
            pair<int, int> coords = decrypt(i);
            grid[coords.first][coords.second] = 0;
        }
    }
}

void removeRegions (int n, int k, vector< vector<int> >& graph, vector< vector<int> >& grid) {
    vector<bool> visited((unsigned long)10 * n);

    for (int i = 0; i < 10 * n; i++) {
        pair<int, int> coords = decrypt(i);
        if (!visited[i] && grid[coords.first][coords.second] != 0) {
            bfs(k, i, visited, graph, grid);
        }
    }
}

void gravity(int n, vector< vector<int> >& grid) {
    for (int i = 0; i < 10; i++) {
        vector<int> left;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 0) {
                left.push_back(grid[i][j]);
            }
        }

        grid[i] = vector<int>((unsigned long)n);
        for (int j = 0; j < left.size(); j++) {
            grid[i][j] = left[j];
        }
    }
}

int main () {
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    int N, K;
    cin >> N >> K;

    vector< vector<int> > grid(10, vector<int>((unsigned long)N));

    // Encoded (x,y) --> 10y + x
    vector< vector<int> > graph((unsigned long)10 * N);
    buildGraph(N, graph);

    // Get grid
    string s;
    for (int i = N - 1; i >= 0; i--) {
        cin >> s;
        for (int j = 0; j < 10; j++) {
            grid[j][i] = s[j] - '0';
        }
    }

    vector< vector<int> > old;
    do {
        old = grid;

        removeRegions(N, K, graph, grid);
        gravity(N, grid);
    } while (old != grid);

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            cout << grid[j][i];
        }
        cout << endl;
    }
    return 0;
}