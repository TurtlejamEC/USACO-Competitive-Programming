/*
ID: elicho21
LANG: C++
TASK: palsquare
*/

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
int main() {
    freopen("palsquare.in", "r", stdin);
    freopen("palsquare.out", "w", stdout);

    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int B;
    cin >> B;
    for (int i = 1; i <= 300; i++) {
        int square = i * i;
        vector<char> converted;
        while (square != 0) {
            converted.push_back(digits[square % B]);
            square /= B;
        }

        int a = i;
        vector<char> aConverted;
        while (a != 0) {
            aConverted.push_back(digits[(a % B)]);
            a /= B;
        }

        bool isPalindrome = true;
        for (int j = 0; j < converted.size() / 2; j++) {
            if (converted[j] != converted[converted.size() - j - 1]) {
                isPalindrome = false;
                break;
            }
        }

        if (isPalindrome) {
            cout << string(aConverted.rbegin(), aConverted.rend()) << " " << string(converted.rbegin(), converted.rend()) << endl;
        }
    }

    return 0;
}