#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Cow {
    int height, index;
};

bool sortHeight(Cow a, Cow b) {
    return a.height > b.height;
}

class Fenwick {
public:
    vector<int> tree;

    void update(int i, int val) {
        for (; i < tree.size(); i += i&-i) {
            tree[i] += val;
        }
    }

    int query(int i) {
        int ans = 0;
        for (; i > 0; i -= i&-i) {
            ans += tree[i];
        }
        return ans;
    }

    Fenwick(vector<Cow>& parent) {
        tree.resize(parent.size() + 1);
    }
};

int main () {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    int N;
    cin >> N;
    vector<Cow> descHeights(N);
    for (int i = 0; i < N; i++) {
        int h;
        cin >> h;
        descHeights[i] = {h, i};
    }

    sort(descHeights.begin(), descHeights.end(), sortHeight);

    Fenwick heightsSeen(descHeights);
    int ans = 0;
    for (int i = 0; i < descHeights.size(); i++) {
        int l = heightsSeen.query(descHeights[i].index + 1);
        int r = i - l;
        if (2 * min(l, r) < max(l, r)) ans++;
        heightsSeen.update(descHeights[i].index + 1, 1);
    }

    cout << ans << endl;

    return 0;
}