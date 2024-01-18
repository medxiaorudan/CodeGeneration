#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <iomanip>

struct UserInput {
    double value;
    std::chrono::system_clock::time_point timestamp;
};

void displayUserInputs(const std::vector<UserInput>& inputs) {
    std::cout << "Sorted User Inputs:" << std::endl;
    for (const auto& input : inputs) {
        std::time_t timestamp = std::chrono::system_clock::to_time_t(input.timestamp);
        std::cout << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S") << ": " << input.value << std::endl;
    }
}

int main() {
    std::vector<UserInput> inputs;

    while (true) {
        std::cout << "Enter a numeric value (or 'q' to quit): ";
        std::string input;
        std::cin >> input;

        if (input == "q") {
            std::cout << "Exiting the program..." << std::endl;
            break;
        }

        try {
            double value = std::stod(input);
            UserInput userInput;
            userInput.value = value;
            userInput.timestamp = std::chrono::system_clock::now();
            inputs.push_back(userInput);
            std::sort(inputs.begin(), inputs.end(), [](const UserInput& a, const UserInput& b) {
                return a.value < b.value;
            });
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a numeric value." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    displayUserInputs(inputs);

    return 0;
}