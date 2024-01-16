#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Record
{
    int input;
    time_t timestamp;
};

int main()
{
    vector<Record> records;

    while(true)
    {
        int input;
        cout << "Enter a number: ";
        cin >> input;

        if(input == 0)
            break;

        Record record;
        record.input = input;
        record.timestamp = time(0);
        records.push_back(record);
    }

    sort(records.begin(), records.end(), [](const Record& r1, const Record& r2) {
        return r1.input < r2.input;
    });

    for(auto& record : records)
    {
        cout << record.input << " " << ctime(&record.timestamp) << endl;
    }

    return 0;
}