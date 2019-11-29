#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegTree {
public:
    vector< vector<int> > tree;
    int parentSize;

    int query(int l, int r, int h) {
        int answer = 0;
        for (l += parentSize, r += parentSize; l < r; l >>= 1, r >>= 1) {
            if (l&1) answer += countGreater(tree[l++], h);
            if (r&1) answer += countGreater(tree[--r], h);
        }
        return answer;
    }

    SegTree(vector<int>& parent) {
        parentSize = parent.size();
        tree.resize(parentSize<<1);
        for (int i = 0; i < parent.size(); i++) {
            tree[parentSize + i] = vector<int>(1, parent[i]);
        }

        for (int i = parentSize - 1; i > 0; i--) {
            tree[i] = mergeNodes(tree[i<<1], tree[i<<1|1]);
        }
    }

private:
    int countGreater(vector<int>& v, int h) {
        auto pos = upper_bound(v.begin(), v.end(), h);
        auto thing = pos - v.begin();
        return v.size() - (pos - v.begin());
    }

    vector<int> mergeNodes(vector<int>& l, vector<int>& r) {
        vector<int> result(l.size() + r.size());
        int i = 0, j = 0, k = 0;
        while (i < l.size() && j < r.size()) {
            if (l[i] < r[j]) {
                result[k] = l[i];
                i++;
            } else {
                result[k] = r[j];
                j++;
            }
            k++;
        }

        while (i < l.size()) {
            result[k] = l[i];
            i++;
            k++;
        }

        while (j < r.size()) {
            result[k] = r[j];
            j++;
            k++;
        }

        return result;
    }
};

int main () {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> heights(N);
    for (int i = 0; i < N; i++) {
        cin >> heights[i];
    }

    SegTree segtree(heights);

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int L = 0, R = 0;
        if (i != 0) {
            L = segtree.query(0, i, heights[i]);
        }
        if (i != N-1) {
            R = segtree.query(i+1, N, heights[i]);
        }
        ans += (max(L, R) > 2*min(L, R));
    }

    cout << ans << endl;

    return 0;
}