/*
ID: elicho21
LANG: C++
TASK: barn1
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {
    freopen("barn1.in", "r", stdin);
    freopen("barn1.out", "w", stdout);

    int M, S, C;
    cin >> M >> S >> C;

    vector<int> occupied(C);

    for (int i = 0; i < C; i++) {
        cin >> occupied[i];
    }
    sort(occupied.begin(), occupied.end());

    vector<int> gaps;

    int first = 0, last = 0;
    int previous = 0;
    for (int i = 0; i < C; i++) {
        int current;
        if (previous != 0) {
            current = occupied[i];
            gaps.push_back(current - previous - 1);
            previous = current;
            last = current;
        } else {
            previous = occupied[i];
            first = previous;
        }
    }

    sort(gaps.begin(), gaps.end());

    int ans = last - first + 1;
    for (int i = 0; i < M - 1; i++) {
        ans -= gaps.back();
        gaps.pop_back();

        if (gaps.size() == 0) {
            break;
        }
    }

    cout << ans << endl;

    return 0;
}