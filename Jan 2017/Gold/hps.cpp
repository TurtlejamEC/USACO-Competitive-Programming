#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// H = 0, P = 1, S = 2
// Therefore (gesture + 1) % 3 == winning gesture

int main () {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int N, K;
    cin >> N >> K;
    vector<int> order(N);

    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;

        if (c == 'H') {
            order[i] = 0;
        } else if (c == 'P') {
            order[i] = 1;
        } else {
            order[i] = 2;
        }
    }

    // Max wins after nth game with at most k changes after playing i
    vector< vector< vector<int> > > ans(N, vector< vector<int> >(K + 1, vector<int>(3)));

    vector<int> gamesWon(3);
    for (int n = 0; n < N; n++) {
        gamesWon[((order[n] + 1) % 3)]++;
        for (int i = 0; i < 3; i++) {
            ans[n][0][i] = gamesWon[i];
        }
    }

    for (int k = 1; k < K + 1; k++) {
        for (int i = 0; i < 3; i++) {
            ans[0][k][i] = ans[0][0][i];
        }
    }

    for (int n = 1; n < N; n++) {
        int win = (order[n] + 1) % 3;
        for (int k = 1; k < K + 1; k++) {
            for (int i = 0; i < 3; i++) {
                // Changed gesture
                int bestChanged = max(ans[n-1][k-1][(i+1)%3], ans[n-1][k-1][(i+2)%3]) + (i == win);

                // Kep gesture
                int bestNoChange = max(ans[n-1][k][i], ans[n][k-1][i]) + (i == win);
                ans[n][k][i] = max(bestChanged, bestNoChange);
            }
        }
    }

    cout << *max_element(ans[N-1][K].begin(), ans[N-1][K].end()) << endl;
}