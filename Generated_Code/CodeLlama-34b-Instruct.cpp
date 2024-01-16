#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, string>> records;
    string input;
    int value;

    while (true) {
        cout << "Enter a number: ";
        cin >> input;
        if (input == "q") break;
        value = stoi(input);
        records.push_back(make_pair(value, input));
        sort(records.begin(), records.end());
        for (auto& record : records) {
            cout << record.second << " " << record.first << endl;
        }
    }

    return 0;
}