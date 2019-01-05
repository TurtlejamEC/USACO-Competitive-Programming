/*
ID: elicho21
LANG: C++
TASK: ariprog
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <set>

using namespace std;

vector<int> bisquares;
vector< vector< vector<int> > > graph;
vector< pair<int, int> > ans;

int N, M;

/*bool sortAns(const pair<int,int> &a,
               const pair<int,int> &b)
{
    return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second);
}

*//*
void search(int index, int difference, vector<int> prog) {
    if (prog.size() == N) {
        ans.push_back({bisquares[prog.front()], difference});
    }

    for (int i = index + 1; i < bisquares.size(); i++) {
        if (difference == -1) {
            difference = bisquares[i] - bisquares[index];
            prog.push_back(i);
            search(i, difference, prog);

            prog.pop_back();
            difference = -1;
        } else if (bisquares[i] - bisquares[prog.back()] == difference) {
            prog.push_back(i);
            search(i, difference, prog);

            prog.pop_back();
        }
    }
}
*//*

void checkVisited (int diff, vector<int> visited) {
    int tmp = visited.size() + 1 - N;
    int limit = max(tmp, 0);
    for (int i = 0; i < limit; i++) {
        ans.push_back(make_pair(bisquares[visited[i]], diff));
    }
}

void dfs (int node, int diff, vector<int> visited) {
    bool end = true;

    for (int i = 0; i < graph[node].size(); i++) {
        if (diff == -1) {
            visited.push_back(graph[node][i][0]);
            graph[node][i][2] = 1;
            dfs(graph[node][i][0], graph[node][i][1], visited);
            visited.pop_back();
            end = false;
        } else {
            if (graph[node][i][1] == diff && graph[node][i][2] == 0) {
                visited.push_back(graph[node][i][0]);
                graph[node][i][2] = 1;
                dfs(graph[node][i][0], diff, visited);
                visited.pop_back();

                end = false;
            }
        }
    }

    if (end) {
        if (visited.size() < N) {
            return;
        }
        checkVisited(diff, visited);
    }
}*/

int main() {
    freopen("ariprog.in", "r", stdin);
    freopen("ariprog.out", "w", stdout);

    cin >> N >> M;
    set<int> bisquares;
    vector<bool> bisquareExists((unsigned long)(M * M + M * M + 1));

    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            int tmp = i * i + j * j;
            bisquares.insert(tmp);
            bisquareExists[tmp] = true;
        }
    }

    /*auto iter = bisquares.begin();
    advance(iter, bisquares.size() / N);*/

    bool printed = false;
    int difference = 1;
    while (difference <= 5000) {
        for (auto it = bisquares.begin(); it != bisquares.end(); ++it) {
            if (*it + (N - 1) * difference <= M * M + M * M ) {
                for (int j = 0; j < N; j++) {
                    if (!bisquareExists[*it + j * difference]) {
                        break;
                    } else {
                        if (j == N - 1) {
                            cout << *it << " " << difference << endl;
                            printed = true;
                        }
                    }
                }
            }
        }

        difference++;
    }

    if (!printed) {
        cout << "NONE" << endl;
    }

    /*for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            int tmp = i * i + j * j;
            bisquares.push_back(tmp);
        }
    }

    sort(bisquares.begin(), bisquares.end());
    bisquares.erase(unique(bisquares.begin(), bisquares.end()), bisquares.end());

    graph.resize(bisquares.size());

    for (int i = 0; i < bisquares.size(); i++) {
        for (int j = i + 1; j < bisquares.size(); j++) {
            vector<int> edge = {j, bisquares[j] - bisquares[i], 0};
            graph[i].push_back(edge);
        }
    }

    for (int i = 0; i < bisquares.size(); i++) {
        vector<int> visited;
        visited.push_back(i);
        dfs(i, -1, visited);
        visited.pop_back();
    }

    vector<int> prog;
    for (int i = 0; i < bisquares.size(); i++) {
        prog.push_back(i);
        search(i, -1, prog);
        prog.pop_back();
    }

    sort(ans.begin(), ans.end(), sortAns);

    for (pair<int, int> i: ans) {
        cout << i.first << " " << i.second << endl;
    }

    if (ans.empty()) {
        cout << "NONE" << endl;
    }*/
    return 0;
}