#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>

// Structure to store input value and its timestamp
struct Record {
    int value;
    std::time_t timestamp;

    // Constructor
    Record(int v) : value(v) {
        timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
};

// Comparison function for sorting
bool compare(const Record& r1, const Record& r2) {
    return r1.value < r2.value;
}

int main() {
    std::vector<Record> records;
    int inputValue;
    std::string line;

    std::cout << "Enter the numeric inputs. Enter -1 to stop input and display results." << std::endl;

    // Get input from the user
    while(true) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if(!(ss >> inputValue)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        
        if(inputValue == -1) {
            break;
        }
        
        records.push_back(Record(inputValue));
    }

    // Sort records
    std::sort(records.begin(), records.end(), compare);

    // Display results
    for(auto& record : records) {
        std::cout << "Value: " << record.value << ", Timestamp: " << std::ctime(&record.timestamp) << std::endl;
    }
    
    return 0;
}
