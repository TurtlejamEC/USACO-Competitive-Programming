#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    int N, M, C;
    cin >> N >> M >> C;

    vector<int> arrivals(N);

    for (int i = 0; i < N; i++) {
        cin >> arrivals[i];
    }

    sort(arrivals.begin(), arrivals.end());

    int hi = *arrivals.rbegin();
    int lo = 0;

    while (lo < hi) {
        int mid = (hi + lo) / 2;

        int wait = 0, cowsInside = 0, busesUsed = 0;

        bool works = true;

        for (int i = 0; i < N; i++) {
            if (cowsInside == 0) {
                wait = 0;
            } else {
                wait += arrivals[i] - arrivals[i - 1];
            }

            if (cowsInside >= C || wait > mid) {
                busesUsed++;
                cowsInside = 0;
                wait = 0;

                if (busesUsed >= M && i < N) {
                    works = false;
                    break;
                }
            }

            cowsInside++;
        }

        if (works) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;

    return 0;
}