#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool inRadius (int x1, int y1, int x2, int y2, int power) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= power * power;
}

int main () {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    int N;
    cin >> N;

    vector< pair<int, int> > cows(N);
    vector<int> power(N);

    for (int i = 0; i < N; i++) {
        int x, y, p;
        cin >> x >> y >> p;
        cows[i] = {x, y};
        power[i] = p;
    }

    vector< vector<int> > graph(N);
    for (int i = 0; i < cows.size(); i++) {
        for (int j = 0; j < cows.size(); j++) {
            if (i == j) continue;

            if (inRadius(cows[i].first, cows[i].second, cows[j].first, cows[j].second, power[i])) {
                graph[i].push_back(j);
            }
        }
    }

    int maxCows = 0;
    for (int i = 0; i < N; i++) {
        int cowsReached = 0;
        vector<bool> visited(N);
        queue<int> next;

        cowsReached++;
        visited[i] = true;
        next.push(i);
        while (!next.empty()) {
            int current = next.front();
            next.pop();

            for (int j: graph[current]) {
                if (visited[j]) continue;

                cowsReached++;
                visited[j] = true;
                next.push(j);
            }
        }

        maxCows = max(maxCows, cowsReached);
    }

    cout << maxCows << endl;

    return 0;
}