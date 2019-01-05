/*
ID: elicho21
LANG: C++
TASK: dualpal
*/

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> convert (int n, int base) {
    vector<int> converted;
    while (n != 0) {
        converted.push_back(n % base);
        n /= base;
    }
    return converted;
}

bool isPalindrome (vector<int> n) {
    bool isPalindrome = true;
    for (int j = 0; j < n.size() / 2; j++) {
        if (n[j] != n[n.size() - j - 1]) {
            isPalindrome = false;
            break;
        }
    }
    return isPalindrome;
}

int main() {
    freopen("dualpal.in", "r", stdin);
    freopen("dualpal.out", "w", stdout);

    int N, S;
    cin >> N >> S;

    int sent = 0;
    int test = S + 1;
    while (sent < N) {
        int pCounter = 0;
        for (int i = 2; i <= 10; i++) {
            if (isPalindrome(convert(test, i))) {
                pCounter++;
            }

            if (pCounter >= 2) {
                cout << test << endl;
                sent++;
                break;
            }
        }
        test++;
    }

    return 0;
}