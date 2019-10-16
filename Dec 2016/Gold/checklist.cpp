#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int dist (pair<int, int> a, pair<int, int> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

void print(vector< vector< vector<int> > >& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            for (int k = 0; k < v[i][k].size(); k++) {
                printf("%4d%4d", v[i][j][0], v[i][j][1]);
            }
        }
        cout << endl;
    }
}

int main () {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    int H, G;
    cin >> H >> G;

    vector<pair<int, int> > hCows(H);
    vector<pair<int, int> > gCows(G);
    for (int i = 0; i < H; i++) {
        int a, b;
        cin >> a >> b;
        hCows[i] = {a, b};
    }

    for (int i = 0; i < G; i++) {
        int a, b;
        cin >> a >> b;
        gCows[i] = {a, b};
    }

    // min cost after going to h[i] and g[j - 1]
    // k = 0 ends on H, k = 1 ends on G
    vector< vector< vector<int> > > ans(H, vector< vector<int> >(G + 1, vector<int>(2, INT_MAX)));

    // Base cases
    ans[0][0][0] = 0;
    ans[0][1][1] = dist(hCows[0], gCows[0]);

    for (int j = 2; j < G + 1; j++) {
        ans[0][j][1] = ans[0][j - 1][1] + dist(gCows[j - 1], gCows[j - 2]);
    }

    for (int i = 1; i < H; i++) {
        ans[i][0][0] = ans[i - 1][0][0] + dist(hCows[i - 1], hCows[i]);
    }

    for (int i = 1; i < H; i++) {
        for (int j = 1; j < G + 1; j++) {
            int HtoH = ans[i - 1][j][0] == INT_MAX ? INT_MAX : ans[i - 1][j][0] + dist(hCows[i - 1], hCows[i]);
            int GtoH = ans[i - 1][j][1] == INT_MAX ? INT_MAX : ans[i - 1][j][1] + dist(gCows[j - 1], hCows[i]);
            int HtoG = ans[i][j - 1][0] == INT_MAX ? INT_MAX : ans[i][j - 1][0] + dist(hCows[i], gCows[j - 1]);
            int GtoG = ans[i][j - 1][1] == INT_MAX ? INT_MAX : ans[i][j - 1][1] + dist(gCows[j - 2], gCows[j - 1]);

            ans[i][j][0] = min(HtoH, GtoH);
            ans[i][j][1] = min(HtoG, abs(GtoG));
        }
    }

    cout << ans[H - 1][G][0] << endl;


    return 0;
}