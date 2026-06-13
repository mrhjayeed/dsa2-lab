#include <bits/stdc++.h>
using namespace std;

void printCharacterFrequency(string str) {
    unordered_map<char, int> frequencyMap;

    for (char ch : str) {
        frequencyMap[ch]++;
    }

    for (auto pair : frequencyMap) {
        cout << pair.first << " " << pair.second << "\n";
    }
}

int main() {
    string str = "programming";
    cout << "Frequency for \"" << str << "\":\n";
    printCharacterFrequency(str);

    return 0;
}