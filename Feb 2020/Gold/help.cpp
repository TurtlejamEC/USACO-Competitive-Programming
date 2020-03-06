#include <iostream>
#include <vector>
#include <algorithm>

const int MOD = 1e9+7;

using namespace std;

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

int main () {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> intervalStart(N);
    vector<int> startStop(2*N+1);
    for (int i = 0; i < N; i++) {
        int l, r;
        cin >> l >> r;
        intervalStart[i] = l;

        startStop[l] = 1;
        startStop[r] = -1;
    }

    vector<int> prefixSum(2*N+1);
    for (int i = 1; i < 2*N+1; i++) {
        prefixSum[i] = prefixSum[i-1] + startStop[i];
    }

    vector<int> power2(N+1, 1);
    for (int i = 1; i < N+1; i++) {
        power2[i] = (power2[i-1] * 2) % MOD;
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int subsetsStarting = N - 1 - prefixSum[intervalStart[i]-1];
        ans = (ans + power2[subsetsStarting]) % MOD;
    }

    cout << ans << endl;
    return 0;
}