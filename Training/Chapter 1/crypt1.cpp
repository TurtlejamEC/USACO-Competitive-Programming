/*
ID: elicho21
LANG: C++
TASK: crypt1
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int ans = 0;

void test (vector<int> digits, vector<int> numbers) {
    if (numbers.size() < 5) {
        for (int i = 0; i < digits.size(); i++) {
            vector<int> added(numbers.begin(), numbers.end());
            added.push_back(digits[i]);
            test(digits, added);
        }
    } else {
        // Top
        int t1 = numbers[0] * 100 + numbers[1] * 10 + numbers[2];
        int t2 = numbers[3] * 10 + numbers[4];

        int m1 = t1 * numbers[4];
        int m2 = t1 * numbers[3];

        int b = t1 * t2;

        if (m1 > 999 || m2 > 999 || t1 * t2 > 9999)
            return;
        else {
            numbers.push_back(m1 / 100);
            numbers.push_back(m1 / 10 % 10);
            numbers.push_back(m1 % 10);

            numbers.push_back(m2 / 100);
            numbers.push_back(m2 / 10 % 10);
            numbers.push_back(m2 % 10);

            numbers.push_back(b / 1000);
            numbers.push_back(b / 100 % 10);
            numbers.push_back(b / 10 % 10);
            numbers.push_back(b % 10);

            for (int i = 0; i < 10; i++) {
                if (find(digits.begin(), digits.end(), numbers[5 + i]) == digits.end())
                    return;
            }

            ans++;
        }
    }
}

int main() {
    freopen("crypt1.in", "r", stdin);
    freopen("crypt1.out", "w", stdout);

    int N;
    cin >> N;

    vector<int> digits(N);
    for (int i = 0; i < N; i++) {
        cin >> digits[i];
    }

    vector<int> tmp;
    test(digits, tmp);

    cout << ans << endl;
    return 0;
}