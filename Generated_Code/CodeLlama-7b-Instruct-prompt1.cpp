#include <iostream>
#include <vector>
#include <chrono>

int main() {
  std::vector<int> inputs;
  std::vector<std::pair<int, std::chrono::time_point<std::chrono::system_clock>>> sorted_inputs;

  // Get user inputs
  while (true) {
    int input;
    std::cout << "Enter a number (or 0 to exit): ";
    std::cin >> input;
    if (input == 0) {
      break;
    }
    inputs.push_back(input);
  }

  // Sort inputs
  for (int input : inputs) {
    sorted_inputs.push_back(std::make_pair(input, std::chrono::system_clock::now()));
  }

  // Display sorted inputs with timestamps
  for (auto& input : sorted_inputs) {
    std::cout << input.first << " (" << input.second << ")" << std::endl;
  }

  return 0;
}