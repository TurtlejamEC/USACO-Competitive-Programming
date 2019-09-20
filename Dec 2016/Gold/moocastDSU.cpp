// 2nd Moocast solution using DSU

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long findDist(pair<int, int> cow1, pair<int, int> cow2) {
    long long squaredDist = (cow1.first - cow2.first) * (cow1.first - cow2.first) +
                            (cow1.second - cow2.second) * (cow1.second - cow2.second);
    return squaredDist;
}

struct connection {
    int a, b;
    long long dist;
};

class DSU {
public:
    struct component {
        int parent;
        int rank;
    };

    vector<component> components;

    int find (int i) {
        if (components[i].parent != i) {
            components[i].parent = find(components[i].parent);
        }

        return components[i].parent;
    }

    void join (int a, int b) {
        int aRoot = components[a].parent;
        int bRoot = components[b].parent;

        if (aRoot == bRoot) return;
        else if (components[aRoot].rank < components[bRoot].rank) {
            components[aRoot].parent = bRoot;
        } else if (components[aRoot].rank > components[bRoot].rank) {
            components[bRoot].parent = aRoot;
        } else {
            components[aRoot].parent = bRoot;
            components[bRoot].rank++;
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

    vector<connection> connections;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            connections.push_back({i, j, findDist(locations[i], locations[j])});
        }
    }

    sort(connections.begin(), connections.end(), [](connection a, connection b) {return a.dist < b.dist;});
    DSU cows(N);
    long long minCost = 0;
    for (int i = 0; i < connections.size(); i++) {
        int cowA = connections[i].a;
        int cowB = connections[i].b;

        if (cows.find(cowA) == cows.find(cowB)) continue;

        minCost = connections[i].dist;

        cows.join(cowA, cowB);
    }

    cout << minCost << endl;

    return 0;
}