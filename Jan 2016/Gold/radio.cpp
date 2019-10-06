#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int energy(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

struct pos {
    int x, y;
};

pos operator +(pos a, pos b) {
    return {a.x + b.x, a.y + b.y};
}

int main () {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    int N, M;
    cin >> N >> M;

    int fx, fy, bx, by;
    cin >> fx >> fy >> bx >> by;

    string john, bessie;
    cin >> john >> bessie;

    map<char, pos> transform;
    transform['N'] = {0, 1};
    transform['E'] = {1, 0};
    transform['S'] = {0, -1};
    transform['W'] = {-1, 0};

    vector < vector<int> > energies(N + 1, vector<int>(M + 1));
    pos f = {fx, fy};
    for (int i = 0; i < N + 1; i++) {
        if (i > 0) {
            f = f + transform[john[i - 1]];
        }

        pos b = {bx, by};
        for (int j = 0; j < M + 1; j++) {
            if (j > 0) {
                b = b + transform[bessie[j - 1]];
            }

            energies[i][j] = energy(f.x, f.y, b.x, b.y);
        }
    }
    energies[0][0] = 0;

    vector< vector<int> > ans(N + 1, vector<int>(M + 1));

    ans[0][0] = energies[0][0];

    for (int i = 1; i < N + 1; i++) {
        ans[i][0] = ans[i - 1][0] + energies[i][0];
    }

    for (int i = 1; i < M + 1; i++) {
        ans[0][i] = ans[0][i - 1] + energies[0][i];
    }

    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < M + 1; j++) {
            int bestPrior = min(min(ans[i - 1][j], ans[i][j - 1]), ans[i - 1][j - 1]);
            ans[i][j] = energies[i][j] + bestPrior;
        }
    }

    cout << ans[N][M] << endl;

    return 0;
}