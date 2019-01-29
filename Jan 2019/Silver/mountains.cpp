#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool comparePeaks(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    int N;
    cin >> N;
    vector< pair<int, int> > peaks(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        peaks[i] = {x, y};
    }

    sort(peaks.begin(), peaks.end(), comparePeaks);

    vector< pair<int, int> > visible;
    for (int i = N - 1; i >= 0; i--) {
        bool canSee = true;
        for (pair<int, int> j: visible) {
            if (peaks[i].second - j.second <= peaks[i].first - j.first && peaks[i].second - j.second <= j.first - peaks[i].first) {
                canSee = false;
                break;
            }
        }

        if (canSee) {
            visible.push_back(peaks[i]);
        }
    }

    cout << visible.size() << endl;

    return 0;
}