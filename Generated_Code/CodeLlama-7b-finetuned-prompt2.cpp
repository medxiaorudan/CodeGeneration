#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
    vector<int> user_inputs;
    vector<pair<int, chrono::time_point<chrono::system_clock>>> user_inputs_with_timestamp;

    cout << "Enter a number: ";
    int user_input;
    while (cin >> user_input)
    {
        user_inputs.push_back(user_input);
        user_inputs_with_timestamp.push_back(make_pair(user_input, chrono::system_clock::now()));
    }

    sort(user_inputs.begin(), user_inputs.end());
    sort(user_inputs_with_timestamp.begin(), user_inputs_with_timestamp.end(), [](const pair<int, chrono::time_point<chrono::system_clock>>& a, const pair<int, chrono::time_point<chrono::system_clock>>& b)
    {
        return a.second < b.second;
    });

    cout << "Sorted user inputs: ";
    for (auto& user_input : user_inputs)
    {
        cout << user_input << " ";
    }
    cout << endl;

    cout << "Sorted user inputs with timestamps: ";
    for (auto& user_input : user_inputs_with_timestamp)
    {
        cout << user_input.first << " ";
        cout << setfill('0') << setw(2) << chrono::duration_cast<chrono::milliseconds>(user_input.second.time_since_epoch()).count() << " ";
    }
    cout << endl;

    return 0;
}