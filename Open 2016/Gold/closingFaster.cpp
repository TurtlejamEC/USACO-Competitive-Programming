// Implementation of provided solution
// Slightly faster than my own

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
    struct component {
        int parent;
        int rank;
    };

public:
    vector<component> components;

    int find(int i) {
        if (components[i].parent != i) {
            components[i].parent = find(components[i].parent);
        }

        return components[i].parent;
    }

    void join (int a, int b) {
        int rootA = find(a), rootB = find(b);

        if (rootA == rootB) return;
        else if (components[rootA].rank < components[rootB].rank) {
            components[rootA].parent = rootB;
        } else if (components[rootA].rank > components[rootB].rank) {
            components[rootB].parent = rootA;
        } else {
            components[rootA].parent = rootB;
            components[rootB].rank++;
        }
    }

    DSU(int n) {
        components = vector<component>(n);
        for (int i = 0; i < n; i++) {
            components[i].parent = i;
            components[i].rank = 1;
        }
    }
};

int main () {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    int N, M;
    cin >> N >> M;

    vector< vector<int> > adj(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> order(N);
    for (int i = N - 1; i >= 0; i--) {
        cin >> order[i];
        order[i]--;
    }

    DSU barns(N);
    int components = 0;
    vector<bool> open(N);
    vector<bool> connected;
    int x = 1;
    for (int i: order) {
        components++;
        open[i] = true;

        for (int j: adj[i]) {
            if (open[j] && barns.find(i) != barns.find(j)) {
                barns.join(i, j);
                components--;
            }
        }

        connected.push_back(components <= 1);
        x++;
    }

    for (int i = N - 1; i >= 0; i--) {
        cout << (connected[i] ? "YES" : "NO") << endl;
    }

    return 0;
}