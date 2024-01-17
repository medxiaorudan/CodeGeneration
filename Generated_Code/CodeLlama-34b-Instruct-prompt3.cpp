#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, string>> record;
    int input;
    string time_stamp;

    while (true) {
        cout << "Enter a number: ";
        cin >> input;
        if (input == -1) break;
        time_stamp = "2023-02-20 12:34:56";
        record.push_back(make_pair(input, time_stamp));
    }

    sort(record.begin(), record.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first < b.first;
    });

    for (const auto& p : record) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}