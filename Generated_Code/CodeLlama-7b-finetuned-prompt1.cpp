#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

int main()
{
    std::vector<std::pair<int, std::string>> user_inputs;
    int input;
    std::string timestamp;
    while (std::cin >> input)
    {
        timestamp = std::to_string(std::time(nullptr));
        user_inputs.push_back(std::make_pair(input, timestamp));
    }
    std::sort(user_inputs.begin(), user_inputs.end());
    for (auto &input : user_inputs)
    {
        std::cout << input.first << " " << input.second << std::endl;
    }
    return 0;
}