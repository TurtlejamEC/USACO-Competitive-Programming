/*
ID: elicho21
LANG: C++
TASK: skidesign
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#define x first
#define y second

using namespace std;

int main() {

    int N = 0;
    int ans = 0;
    vector< pair<int, int> > hills;

    freopen("skidesign.in", "r", stdin);
    freopen("skidesign.out", "w", stdout);

    cin >> N;
    hills.resize(N);
    for (int i = 0; i < N; i++) {
        int hill;
        cin >> hill;
        hills[i] = make_pair(hill, 0);
    }

    sort(hills.begin(), hills.end());

    if (N == 1) {
        cout << 0 << endl;
        return 0;
    } else {
        while (hills[N - 1].x - hills[0].x > 17) {
            int loSum = 0, hiSum = 0;
            int lo = hills[0].x;
            int hi = hills[N - 1].x;

            // Calculate cost of changing lower end and higher end. Find lower cost.
            int i = 0;
            while (hills[i].x == lo) {
                loSum += (hills[i].y + 1) * (hills[i].y + 1) - (hills[i].y) * (hills[i].y);
                i++;
            }

            i = N - 1;
            while (hills[i].x == hi) {
                hiSum += (hills[i].y + 1) * (hills[i].y + 1) - (hills[i].y) * (hills[i].y);
                i--;
            }

            // Edit the cheaper end
            if (loSum <= hiSum) {
                i = 0;
                while (hills[i].x == lo) {
                    hills[i].x++;
                    hills[i].y++;
                    i++;
                }
            } else {
                i = N - 1;
                while (hills[i].x == hi) {
                    hills[i].x--;
                    hills[i].y++;
                    i--;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        ans += hills[i].y * hills[i].y;
    }

    cout << ans << endl;

    return 0;
}