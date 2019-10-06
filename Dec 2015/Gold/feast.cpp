#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    int T, A, B;
    cin >> T >> A >> B;

    vector<bool> canBe(T + 1);
    vector<bool> canHalvedBe(T + 1);
    int maxFullness = 0;
    int maxHalvedFullness = 0;

    canBe[0] = true;
    for (int i = 0; i < T + 1; i++) {
        if (!canBe[i]) continue;

        if (i + A <= T) {
            canBe[i + A] = true;
        }

        if (i + B <= T) {
            canBe[i + B] = true;
        }

        canHalvedBe[i / 2] = true;

        maxFullness = i;
    }

    for (int i = 0; i < T + 1; i++) {
        if (!canHalvedBe[i]) continue;

        if (i + A <= T) {
            canHalvedBe[i + A] = true;
        }

        if (i + B <= T) {
            canHalvedBe[i + B] = true;
        }

        maxHalvedFullness = i;
    }

    cout << max(maxFullness, maxHalvedFullness) << endl;

    return 0;
}