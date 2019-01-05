#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);

    int N;
    cin >> N;

    set<int> bessie, elsie;
    vector<bool> determiner(2 * N);

    for (int i = 0; i < N; i++) {
        int card;
        cin >> card;

        determiner[card - 1] = true;
    }

    for (int i = 0; i < 2 * N; i++) {
        if (determiner[i]) {
            elsie.insert(i + 1);
        } else {
            bessie.insert(i + 1);
        }
    }

    int ans = 0;
    while (!elsie.empty()) {
        if (*bessie.rbegin() < *elsie.rbegin()) {
            bessie.erase(*bessie.begin());
            elsie.erase(*elsie.rbegin());
        } else {
            bessie.erase(bessie.upper_bound(*elsie.rbegin()));
            elsie.erase(*elsie.rbegin());

            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}