#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

int main() {
    vector<string> userInputs;
    string input;

    while (true) {
        cout << "Enter a string: ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        userInputs.push_back(input);
    }

    sort(userInputs.begin(), userInputs.end());

    for (int i = 0; i < userInputs.size(); i++) {
        auto timestamp = chrono::system_clock::now();
        cout << setw(20) << left << userInputs[i] << " " << timestamp << endl;
    }

    return 0;
}