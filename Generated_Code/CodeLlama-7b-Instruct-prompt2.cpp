#include <iostream>
#include <string>
#include <vector>
#include <chrono>

int main()
{
    std::vector<std::string> inputs;
    std::string input;
    while (std::cin >> input)
    {
        inputs.push_back(input);
    }

    std::sort(inputs.begin(), inputs.end());

    for (const auto& input : inputs)
    {
        std::cout << input << " ";
    }

    return 0;
}