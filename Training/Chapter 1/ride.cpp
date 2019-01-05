/*
ID: elicho21
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream fin ("ride.in");
    ofstream fout ("ride.out");

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<char, int> alphabetKey;

    for (int i = 0; i < 26; i++) {
        alphabetKey[alphabet[i]] = i + 1;
    }

    string comet, group;
    int productC = 1;
    int productG = 1;
    fin >> comet >> group;
    for (int i = 0; i < comet.size(); i++) {
          productC *= alphabetKey[comet[i]];
    }
    for (int i = 0; i < group.size(); i++) {
        productG *= alphabetKey[group[i]];
    }
    if ((productC % 47) == (productG % 47))
        fout << "GO" << endl;
    else
        fout << "STAY" << endl;
    return 0;
}