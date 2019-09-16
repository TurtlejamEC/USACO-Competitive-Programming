#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

long double roundToTenths(long double num) {
    return (long long)(num * 10 + 0.5) / 10.0;
}

#define INF 2000000000

int main () {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int N;
    cin >> N;
    vector<long long> haybales(N);
    for (int i = 0; i < N; i++) {
        cin >> haybales[i];
    }

    sort(haybales.begin(), haybales.end());

    vector<long long> minRToLeft(N), minRToRight(N);
    int changed = 0;
    for (int i = 1; i < minRToLeft.size(); i++) {
        if (haybales[i] - haybales[i - 1] > minRToLeft[i - 1]) {
            // Current radius can't reach previous explosion
            minRToLeft[i] = haybales[i] - haybales[i - 1];
            changed = i;
        } else {
            if (haybales[i] - minRToLeft[i - 1] <= haybales[changed - 1]) {
                // Current radius is sufficient
                minRToLeft[i] = minRToLeft[i - 1];
            } else {
                // Increase radius by 1 because this explosion will lead to previous one, needing 1 more than previous
                // radius due to reduction
                minRToLeft[i] = minRToLeft[i - 1] + 1;
                changed = i;
            }
        }
    }

    changed = minRToRight.size() - 1;
    for (int i = minRToRight.size() - 2; i >= 0; i--) {
        if (haybales[i + 1] - haybales[i] > minRToRight[i + 1]) {
            // Current radius can't reach previous explosion
            minRToRight[i] = haybales[i + 1] - haybales[i];
            changed = i;
        } else {
            if (haybales[i] + minRToRight[i + 1] >= haybales[changed + 1]) {
                // Current radius is sufficient
                minRToRight[i] = minRToRight[i + 1];
            } else {
                // Increase radius by 1 because this explosion will lead to previous one, needing 1 more than previous
                // radius due to reduction
                minRToRight[i] = minRToRight[i + 1] + 1;
                changed = i;
            }
        }
    }

    long double lo = 0, hi = 1000000000, currentMid = (lo + hi) / 2;
    while (abs(roundToTenths(hi) - roundToTenths(lo)) > 0) {
        int startFromLeft = upper_bound(minRToLeft.begin(), minRToLeft.end(), currentMid - 1) - minRToLeft.begin() - 1;
        int startFromRight = lower_bound(minRToRight.begin(), minRToRight.end(), currentMid - 1, greater<long long>()) - minRToRight.begin();

        bool currentTooSmall;
        if (startFromRight > startFromLeft) {
            // No overlap in starting positions

            if (haybales[startFromRight] - haybales[startFromLeft] > 2 * currentMid) {
                // current R cannot cover both starts
                currentTooSmall = true;
            } else {
                // Start from the furthest you can go by reaching out with full circle
                long double furthestStartFromLeft = haybales[startFromLeft] + 2 * currentMid;
                int reachedBaleFromLeft = upper_bound(haybales.begin(), haybales.end(), furthestStartFromLeft) - haybales.begin() - 1;
                long double furthestStartFromRight = haybales[startFromRight] - 2 * currentMid;
                int reachedBaleFromRight = lower_bound(haybales.begin(), haybales.end(), furthestStartFromRight) - haybales.begin();
                currentTooSmall = minRToRight[reachedBaleFromLeft] > currentMid - 1 && minRToLeft[reachedBaleFromRight] > currentMid - 1;
            }
        } else {
            currentTooSmall = false;
        }

        if (currentTooSmall) {
            lo = currentMid;
        } else {
            hi = currentMid;
        }
        currentMid = (lo + hi) / 2;
    }

    cout << setprecision(1) << fixed << currentMid << endl;

    return 0;
}