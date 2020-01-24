#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main () {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    int N, M, C;
    cin >> N >> M >> C;

    vector<int> mooney(N);
    for (int i = 0; i < N; i++) {
        cin >> mooney[i];
    }

    vector< vector<int> > adj(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    // dp[t][n] = maximum profit at node n after time t
    vector< vector<int> > dp(1001, vector<int>(N));

    for (int i: adj[0]) {
        dp[1][i] = mooney[i];
    }

    for (int t = 1; t < 1000; t++) {
        for (int n = 0; n < N; n++) {
            for (int i: adj[n]) {
                if (dp[t][n]) {
                    dp[t + 1][i] = max(dp[t + 1][i], dp[t][n] + mooney[i]);
                }
            }
        }
    }

    int ans = 0;
    for (int t = 0; t < 1001; t++) {
        ans = max(ans, dp[t][0] - C*t*t);
    }

    cout << ans << endl;

    return 0;
}