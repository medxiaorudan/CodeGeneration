#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    vector<string> userInputs;
    vector<time_t> timestamps;

    // Get user inputs and timestamps
    for (int i = 0; i < 5; i++) {
        string input;
        cin >> input;
        userInputs.push_back(input);
        timestamps.push_back(time(0));
    }

    // Sort user inputs and timestamps
    sort(userInputs.begin(), userInputs.end());
    sort(timestamps.begin(), timestamps.end());

    // Display sorted user inputs and timestamps
    for (int i = 0; i < userInputs.size(); i++) {
        cout << userInputs[i] << " " << timestamps[i] << endl;
    }

    return 0;
}