#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class SegTree {
public:
    vector<int> tree;
    int parentSize;

    int update(int i, int val) {
        for (tree[i += parentSize] = val; i > 1; i>>=1) {
            tree[i>>1] = tree[i] + tree[i^1];
        }
    }

    int query(int l, int r) {
        int ans = 0;
        for (l += parentSize, r += parentSize; l < r; l >>= 1, r >>= 1) {
            if (l&1) ans += tree[l++];
            if (r&1) ans += tree[--r];
        }
        return ans;
    }

    SegTree(vector<int>& parent) {
        parentSize = parent.size();
        tree.resize(2*parent.size());
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
    SegTree segTree(circle);
    int ans = 0;
    for (int i = 0; i < circle.size(); i++) {
        if (seen[circle[i]]) {
            ans += segTree.query(startEnd[circle[i]].first + 1, startEnd[circle[i]].second);
            segTree.update(startEnd[circle[i]].first, -1);
            segTree.update(startEnd[circle[i]].second, 1);
        } else {
            seen[circle[i]] = true;
            segTree.update(i, 1);
        }
    }

    cout << ans / 2 << endl;

    return 0;
}