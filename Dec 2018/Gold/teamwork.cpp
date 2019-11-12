#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    int N, K;
    cin >> N >> K;

    vector<int> s(N);

    for (int i = 0; i < N; i++) {
        cin >> s[i];
    }

    // ans[N][K] = ans in [0,N] currently in a group of K+1 things
    vector< vector<int> > ans(N, vector<int>(K));

    // max[N][K] = largest number in [N-K,N]
    vector< vector<int> > maxS(N, vector<int>(K));

    for (int k = 0; k < K; k++) {
        ans[0][k] = s[0];
        maxS[0][k] = s[0];
    }

    for (int n = 1; n < N; n++) {
        ans[n][0] = ans[n-1][K-1] + s[n];
        maxS[n][0] = s[n];

        for (int k = 1; k < K; k++) {
            if (n - (k+1) < 0) {
                maxS[n][k] = maxS[n][k-1];
                ans[n][k] = max(ans[n][k-1], (n+1) * maxS[n][k]);
            } else {
                maxS[n][k] = max(maxS[n-1][k-1], s[n]);
                ans[n][k] = max(ans[n][k-1], ans[n-(k+1)][K-1] + maxS[n][k] * (k+1));
            }
        }
    }
    cout << ans[N-1][K-1] << endl;

    return 0;
}