#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    vector<pair<int, time_t>> input_record;
    int input;
    time_t time_stamp;

    while (true) {
        cout << "Enter a number: ";
        cin >> input;
        time_stamp = time(NULL);
        input_record.push_back(make_pair(input, time_stamp));
        sort(input_record.begin(), input_record.end());
        for (auto& record : input_record) {
            cout << record.first << " " << record.second << endl;
        }
    }

    return 0;
}