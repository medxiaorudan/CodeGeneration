#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

struct InputRecord {
    int input;
    std::time_t timestamp;
};

std::time_t getCurrentTimestamp() {
    return std::time(nullptr);
}

std::string getFormattedTime(const std::time_t& time) {
    std::stringstream ss;
    ss << std::asctime(std::localtime(&time));
    std::string str = ss.str();
    str.pop_back(); // remove the newline character
    return str;
}

int main() {
    std::vector<InputRecord> inputRecords;

    while (true) {
        std::cout << "Enter a number (or 'q' to quit): ";
        std::string line;
        std::getline(std::cin, line);
        if (line == "q") {
            break;
        }

        std::istringstream iss(line);
        int input;
        if (!(iss >> input)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        InputRecord record;
        record.input = input;
        record.timestamp = getCurrentTimestamp();
    
        inputRecords.push_back(record);
    }

    std::sort(inputRecords.begin(), inputRecords.end(), [](const InputRecord& a, const InputRecord& b) {
        return a.input < b.input;
    });

    std::cout << "Sorted Inputs:\n";
    for (const auto& record : inputRecords) {
        std::cout << "Input: " << record.input << ", Timestamp: " << getFormattedTime(record.timestamp) << "\n";
    }

    return 0;
}