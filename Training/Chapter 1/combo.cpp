/*
ID: elicho21
LANG: C++
TASK: combo
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> combo(6);

    cin >> combo[0] >> combo[1] >> combo[2] >> combo[3] >> combo[4] >> combo[5];

    int factor = min(5, N);
    int possible = factor * factor * factor * 2;
    vector<int> overlaps(3);
    for (int i = 0; i < 3; i++) {
        if (factor < 5) {
            overlaps[i] = factor;
        } else {
            int case1 = (N + ((combo[0 + i] - combo[3 + i]) % N)) % N;
            int case2 = (N + ((combo[3 + i] - combo[0 + i]) % N)) % N;
            overlaps[i] = max(-1 * min(case1, case2) + 5, 0);
        }
    }

    possible -= overlaps[0] * overlaps[1] * overlaps[2];
    cout << possible << endl;

    return 0;
}