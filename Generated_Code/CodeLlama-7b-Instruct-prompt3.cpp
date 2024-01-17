#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Record {
    int input;
    time_t time;
};

bool compare(const Record& a, const Record& b) {
    return a.input < b.input;
}

int main() {
    vector<Record> records;
    int input;
    time_t time;

    while (cin >> input) {
        time = time(NULL);
        records.push_back({input, time});
    }

    sort(records.begin(), records.end(), compare);

    for (const auto& record : records) {
        cout << record.input << " " << record.time << endl;
    }

    return 0;
}