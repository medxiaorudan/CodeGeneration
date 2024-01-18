#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

// Helper struct to store user inputs with timestamps
struct Record {
    int number;
    std::chrono::system_clock::time_point timestamp;

    Record(int num, std::chrono::system_clock::time_point time):
    number(num), timestamp(time)
    {}
};

// Function to format and display timestamp
std::string formatTime(std::chrono::system_clock::time_point time) {
    auto converted = std::chrono::system_clock::to_time_t(time);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&converted), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Function to print records sorted by user input
void printRecords(const std::vector<Record>& records) {
    for (const auto &record : records) {
        std::cout << "User Input: " << record.number << " Timestamp: " << formatTime(record.timestamp) << '\n';
    }
}

int main() {
    std::vector<Record> records;

    while (true) {
        std::cout << "Enter a number (or any non-numeric character to quit): ";
        int num;
        if (!(std::cin >> num)) {
            std::cout << "Error: Invalid input detected. Exiting program.\n";
            break;
        }
        
        // Record user input with current timestamp
        records.push_back(Record(num, std::chrono::system_clock::now()));

        // Sort the records in ascending order based on user input
        std::sort(records.begin(), records.end(), [](const Record& a, const Record& b){ return a.number < b.number; });

        // Print the sorted records
        printRecords(records);
    }

    return 0;
}