#include <iostream>
#include <vector>

using namespace std;

void pour(pair<int, int>& from, pair<int, int>& to) {
    int transferred = min(from.second, to.first - to.second);
    from.second -= transferred;
    to.second += transferred;
}

int main () {
    freopen("mixmilk.in", "r", stdin);
    freopen("mixmilk.out", "w", stdout);

    int c, m;

    vector< pair<int, int> > buckets(3);

    for (int i = 0; i < 3; i++) {
        int c, m;
        cin >> c >> m;
        buckets[i] = {c, m};
    }

    for (int i = 0; i < 100; i++) {
        int from = i % 3;
        int to = (i+1)%3;
        pour(buckets[from], buckets[to]);
    }

    for (pair<int, int> i: buckets) {
        cout << i.second << endl;
    }

    return 0;
}