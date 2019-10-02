#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class DSU {
    struct component {
        int parent;
        int rank;
    };

public:
    vector<component> components;

    int find (int i) {
        if (components[i].parent != i) {
            components[i].parent = find(components[i].parent);
        }

        return components[i].parent;
    }

    void join (int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

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
        a -= 1;
        b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> order(N);
    for (int i = N - 1; i >= 0; i--) {
        int a;
        cin >> a;
        a -= 1;
        order[i] = a;
    }

    DSU barns(N);
    vector<bool> open(N);
    set<int> needToCheck;
    vector<bool> ans;

    for (int i: order) {
        open[i] = true;

        for (int j: adj[i]) {
            if (open[j]) {
                barns.join(i, j);
            }
        }

        bool allConnected = true;
        for (auto j = needToCheck.begin(); j != needToCheck.end();) {
            if (barns.find(i) == barns.find(*j)) {
                j = needToCheck.erase(j);
            } else {
                allConnected = false;
                j++;
            }
        }

        needToCheck.insert(i);
        ans.push_back(allConnected);
    }

    for (int i = N - 1; i >= 0; i--) {
        if (ans[i]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }


    return 0;
}