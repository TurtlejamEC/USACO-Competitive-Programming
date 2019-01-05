#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main () {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    // {arrival, seniority}
    set< pair<int, int> > arrivals;

    int N;
    cin >> N;

    // durations[seniority] = duration;
    vector<int> durations(N) ;

    for (int i = 0; i < N; i++) {
        int a, t;
        cin >> a >> t;

        arrivals.insert({a, i});
        durations[i] = t;
    }


    // {seniority, arrival}
    set< pair<int, int> > waiting;
    int time = 0;
    int ans = 0;
    while (!arrivals.empty()) {
        while (!arrivals.empty() && arrivals.begin()->first <= time) {
            waiting.insert({arrivals.begin()->second, arrivals.begin()->first});
            arrivals.erase(arrivals.begin());
        }

        if (waiting.empty()) {
            pair<int, int> next = *arrivals.begin();
            time = next.first + durations[next.second];
            arrivals.erase(arrivals.begin());
        } else {
            pair<int, int> next = *waiting.begin();
            ans = max(time - next.second, ans);
            time += durations[next.first];
            waiting.erase(waiting.begin());
        }
    }

    cout << ans << endl;

    return 0;
}