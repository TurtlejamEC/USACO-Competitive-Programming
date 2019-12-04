// Implementing provided solution

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
public:
    vector<int> tree;

    void update(int i, int delta) {
        for (i++; i<tree.size(); i += i&-i) {
            tree[i] += delta;
        }
    }

    int query(int i) {
        int ans = 0;
        for (i++; i > 0; i -= i&-i) {
            ans += tree[i];
        }
        return ans;
    }

    FenwickTree(vector<int>& parent) {
        tree.resize(parent.size()+1);
    }
};

int main () {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    int N;
    cin >> N;
    vector<int> circle(2*N);
    // store start to end
    vector< pair<int, int> > startEnd(N+1);
    vector<bool> hasStart(N+1);
    for (int i = 0; i < 2*N; i++) {
        cin >> circle[i];

        if (hasStart[circle[i]]) {
            startEnd[circle[i]].second = i;
        } else {
            startEnd[circle[i]].first = i;
            hasStart[circle[i]] = true;
        }
    }

    vector<bool> seen(N+1);
    FenwickTree fenwick(circle);
    int ans = 0;
    for (int i = 0; i < circle.size(); i++) {
        if (seen[circle[i]]) {
            fenwick.update(startEnd[circle[i]].first, -1);
            ans += (fenwick.query(i) - fenwick.query(startEnd[circle[i]].first));
        } else {
            seen[circle[i]] = true;
            fenwick.update(i, 1);
        }
    }

    cout << ans << endl;

    return 0;
}