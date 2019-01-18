#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool compareEvents (pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second > b.second;
    } else {
        return a.first < b.first;
    }
}

int main () {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int N;
    cin >> N;

    vector< pair<int, int> > events;
    // Negative id = start, positive id = end
    for (int i = 1; i <= N; i++) {
        int start, end;
        cin >> start >> end;
        events.push_back({start, -i});
        events.push_back({end, i});
    }

    sort(events.begin(), events.end(), compareEvents);

    vector<int> frees(N + 1);
    pair<int, int> firstWatcher;
    int numWatching = 0;
    int totalTime = 0, sTime = 0;
    set<int> watching;
    bool beforeZero = true;
    for (int i = 0; i < 2 * N; i++) {
        if (events[i].second < 0) { // Beginning
            if (numWatching == 0) {
                firstWatcher = events[i];
            } else if (numWatching == 1) {
                frees[-firstWatcher.second] += events[i].first - firstWatcher.first;
            }

            watching.insert(-events[i].second);
            numWatching++;
        } else { // Stopping
            watching.erase(events[i].second);

            if (numWatching == 1) {
                frees[-firstWatcher.second] += events[i].first - firstWatcher.first;
            } else if (numWatching == 2) {
                firstWatcher = {events[i].first, -*watching.begin()};
            }

            numWatching--;
        }

        if (beforeZero) {
            sTime = events[i].first;
            beforeZero = false;
        } else if (!beforeZero && numWatching == 0) {
            totalTime += events[i].first - sTime;
            beforeZero = true;
        }
    }

    cout << totalTime - *min_element(frees.begin() + 1, frees.end()) << endl;


    return 0;
}