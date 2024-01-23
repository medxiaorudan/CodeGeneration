#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Record {
    int input;
    string time;
};

int main() {
    vector<Record> records;
    int input;
    string time;

    while (true) {
        cout << "Enter a number: ";
        cin >> input;

        time = to_string(time_t(time(0)));

        records.push_back({input, time});

        sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
            return a.input < b.input;
        });

        cout << "Previous records: " << endl;
        for (const auto& record : records) {
            cout << record.input << " " << record.time << endl;
        }
    }

    return 0;
}