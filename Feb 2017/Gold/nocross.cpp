#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximize(int last1, int last2, vector<int>& side1, vector<int>& side2, vector< vector<int> >& memo) {
    if (memo[last1][last2] != -1) return memo[last1][last2];

    if (last1 == 0 && last2 == 0) { // Base case: only one from each side
        memo[0][0] = abs(side1[0] - side2[0]) <= 4;
        return memo[0][0];
    } else if (last1 == 0) { // Base case: only one on side 1
        if (abs(side1[0] - side2[last2]) <= 4) {
            memo[0][last2] = 1;
        } else {
            memo[0][last2] = max(0, memo[0][last2 - 1]);
        }
        return memo[0][last2];
    } else if (last2 == 0) { // Base case: only one on side 2
        if (abs(side1[last1] - side2[0]) <= 4) {
            memo[last1][0] = 1;
        } else {
            memo[last1][0] = max(0, memo[last1 - 1][0]);
        }
        return memo[last1][0];
    }

    // Make a connection
    int maxWhenConnecting = 0;
    for (int i = last2; i >= 0; i--) {
        if (abs(side1[last1] - side2[i]) <= 4) {
            if (memo[last1 - 1][i - 1] == -1) {
                maxWhenConnecting = maximize(last1 - 1, i - 1, side1, side2, memo);
            } else {
                maxWhenConnecting = memo[last1 - 1][i - 1];
            }
            maxWhenConnecting++;
            break;
        }
    }

    // Don't make a connection
    int maxWhenNot = 0;
    if (memo[last1 - 1][last2] == -1) {
        maxWhenNot = maximize(last1 - 1, last2, side1, side2, memo);
    } else {
        maxWhenNot = memo[last1 - 1][last2];
    }

    memo[last1][last2] = max(maxWhenConnecting, maxWhenNot);
    return memo[last1][last2];
}

int main () {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> side1(N), side2(N);
    vector< vector<int> > memo(N, vector<int>(N, -1));


    for (int i = 0; i < N; i++) {
        cin >> side1[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> side2[i];
    }

    cout << maximize(N - 1, N - 1, side1, side2, memo) << endl;

    return 0;
}