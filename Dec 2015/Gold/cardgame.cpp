#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> bessie, elsieFirst, elsieSecond;
    vector<bool> elsieCards(2 * N + 1);

    for (int i = 0; i < N / 2; i++) {
        int nextCard;
        cin >> nextCard;
        elsieCards[nextCard] = true;
        elsieFirst.push_back(nextCard);
    }

    for (int i = N / 2; i < N; i++) {
        int nextCard;
        cin >> nextCard;
        elsieCards[nextCard] = true;
        elsieSecond.push_back(nextCard);
    }

    for (int i = 1; i < 2 * N + 1; i++) {
        if (!elsieCards[i]) {
            bessie.push_back(i);
        }
    }

    sort(elsieFirst.rbegin(), elsieFirst.rend());
    sort(elsieSecond.begin(), elsieSecond.end());

    int score = 0;
    for (int i = 0; i < elsieFirst.size(); i++) {
        if (elsieFirst[i] > bessie.back()) {
            continue;
        }
        score++;
        bessie.pop_back();
    }

    sort(bessie.rbegin(), bessie.rend());
    for (int i = 0; i < elsieSecond.size(); i++) {
        if (elsieSecond[i] < bessie.back()) {
            continue;
        }
        score++;
        bessie.pop_back();
    }

    cout << score << endl;

    return 0;
}