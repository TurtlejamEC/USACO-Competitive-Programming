#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007
#define ull unsigned long long

using namespace std;

ull power(ull b, ull p) {
    if (p == 0) return 1;

    ull halfResult = power(b, p/2);
    if (p % 2 == 0) {
        return (halfResult * halfResult) % MOD;
    } else {
        return ((halfResult * halfResult) % MOD * b) % MOD;
    }
}

int main () {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);

    int N, M, K;
    cin >> N >> M >> K;

    vector< pair<int, int> > words(N);

    for (int i = 0; i < N; i++) {
        int s, c;
        cin >> s >> c;
        words[i] = {s, c};
    }

    // combos[i] = number of combos of length i
    vector<ull> combos(K + 1);
    combos[0] = 1;

    // lines[i] = combos of lines ending in rhyme class i
    vector<ull> lines(N + 1);

    for (int i = 0; i <= K; i++) {
        for (int j = 0; j < N; j++) {
            if (i < words[j].first) continue;

            if (i == K) {
                lines[words[j].second] = (lines[words[j].second] + combos[i - words[j].first]) % MOD;
                continue;
            }

            combos[i] = (combos[i] + combos[i - words[j].first]) % MOD;
        }
    }

    vector<int> numberOfE(26);
    for (int i = 0; i < M; i++) {
        char c;
        cin >> c;
        numberOfE[c - 'A']++;
    }

    ull ans = 1;
    for (int i = 0; i < 26; i++) {
        if (!numberOfE[i]) continue;

        ull allEndI = 0;
        for (int j = 1; j < N+1; j++) {
            allEndI = (allEndI + power(lines[j], numberOfE[i])) % MOD;
        }
        ans = (ans * allEndI) % MOD;
    }

    cout << ans << endl;

    return 0;
}