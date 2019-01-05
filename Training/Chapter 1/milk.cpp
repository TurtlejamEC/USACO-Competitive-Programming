/*
ID: elicho21
LANG: C++
TASK: milk
*/

#define x first
#define y second

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

bool sortY(const pair<int,int> &a, const pair<int,int> &b) {
    return (a.x > b.x);
}

int main() {
    freopen("milk.in", "r", stdin);
    freopen("milk.out", "w", stdout);

    int N, M;
    cin >> N >> M;

    vector< pair <int, int> > farmers(M);
    for (int i = 0; i < M; i++) {
        int P, A;
        cin >> P >> A;
        farmers[i] = {P, A};
    }

    sort(farmers.begin(), farmers.end(), sortY);

    int cost = 0;
    while (N > 0) {
        int amount = 0;
        if (N >= farmers.back().y) {
            amount = farmers.back().y;
        } else {
            amount = N;
        }

        N -= amount;
        cost += amount * farmers.back().x;
        farmers.pop_back();
    }

    cout << cost << endl;

    return 0;
}