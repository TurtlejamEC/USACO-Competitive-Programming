#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int N, K;
    cin >> N >> K;

    vector<int> haybales(N);
    for (int i = 0; i < N; i++) {
        cin >> haybales[i];
    }

    sort(haybales.begin(), haybales.end());

    int r = 0, lo = *haybales.begin(), hi = *haybales.rbegin();
    while (lo < hi) {
        r = (lo + hi) / 2;

        int cowsLeft = K, startX = 0;
        bool including = false, enough = true;
        for (int i = 0; i < N; i++) {
            if (including) {
                if (haybales[i] - startX > 2 * r) {
                    cowsLeft--;
                    including = false;
                } else {
                    continue;
                }
            }
            if (cowsLeft == 0) {
                enough = false;
                break;
            }
            including = true;
            startX = haybales[i];
        }

        if (enough) {
            hi = r;
        } else {
            lo = r + 1;
        }
    }

    r = lo;

    cout << r << endl;

    return 0;
}