#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>



// Function to run a command and capture its output
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}


// Function to run the program with input redirection
std::string runProgramWithInput(const std::string& inputCommand, const std::string& input) {
    // Create a temporary file to store the input
    std::ofstream inputfile("temp_input.txt");
    inputfile << input;
    inputfile.close();

    // Run the program with input redirection
    std::string command = inputCommand + " < temp_input.txt";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    // Remove the temporary input file
    remove("temp_input.txt");

    return result;
}

// Helper function to check if values are in ascending order
bool areValuesInAscendingOrder(const std::string& programOutput) {
    std::istringstream outputStream(programOutput);
    std::string line;

    // Collect numbers from the Value lines
    std::vector<int> values;
    while (std::getline(outputStream, line)) {
        if (line.find("Value:") != std::string::npos) {
            int value = std::stoi(line.substr(line.find(":") + 2));
            values.push_back(value);
        }
    }

    // Check if the numbers are in ascending order
    return std::is_sorted(values.begin(), values.end());
}

bool areValuesInAscendingOrder2(const std::string& programOutput) {
    std::istringstream outputStream(programOutput);
    std::string line;

    // Collect numbers from lines
    std::vector<int> values;

    // Process each line individually
    while (std::getline(outputStream, line, '\n')) {
        // Find the first position of a digit or minus sign
        size_t pos = line.find_first_of("0123456789-");

        if (pos != std::string::npos) {
            // Find the position of the first non-digit after the optional minus sign
            size_t endPos = line.find_first_not_of("0123456789", pos + 1);

            // Extract the number (including possible negative sign)
            int value = std::stoi(line.substr(pos, endPos - pos));
            values.push_back(value);
        }
    }
    // Remove the first element if it is -1
    if (!values.empty() && values[0] == -1) {
        values.erase(values.begin());
    } 

    // Print the values before returning
    std::cout << "Values: ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

 
    // Check if the numbers are in ascending order
    bool isAscending = std::is_sorted(values.begin(), values.end());

    // Print whether the numbers are in ascending order
    std::cout << "Values are in ascending order: " << std::boolalpha << isAscending << std::endl;

    // Return whether the numbers are in ascending order
    return isAscending;
}


// Function to run a test case on a given program and check if it passes
void runTest(const std::string& programPath) {
    // Build and run the program, capturing the output
    std::string buildCommand = "g++ -o testprog ../" + programPath;

    std::cout << buildCommand << "\n";


    std::string buildOutput = exec(buildCommand.c_str());
    // std::cout << buildOutput << "\n";
    // This should fail if the code doesnt compile
    REQUIRE(buildOutput.find("error") == std::string::npos);

    std::string runCommand = "testprog";

    // Test case 1: Check if the program accepts numeric input
    std::string input = "5\n20\n-3\n-1\nq\nexit";
    std::cout << runCommand << "\n";

    std::string output = runProgramWithInput(runCommand, input);
    
    // Assuming your program outputs the entered number as well, you can check for the expected output
    std::cout << output << "\n";

    // REQUIRE(output.find("Enter a number:") != std::string::npos);

    // Test case 2: Check if the outputs have timestamps
    // std::cout << output.find("Timestamp") << "\n";


    REQUIRE(output.find("Jan") != std::string::npos);

    // Test case 3: Check if the number inputs in ascending order
    bool isAscending = areValuesInAscendingOrder2(output);

    REQUIRE(isAscending);
}

TEST_CASE("Test Langchain_GPT4.cpp", "[Langchain_GPT4]") {
    runTest("Langchain_GPT4.cpp");
}


TEST_CASE("Test Langchain_GPT3.5_turbo.cpp", "[Langchain_GPT3.5_turbo]") {
    runTest("Langchain_GPT3.5_turbo.cpp");
}


TEST_CASE("Test CodeLlama-7b-finetuned.cpp", "[CodeLlama-7b-finetuned]") {
    runTest("CodeLlama-7b-finetuned.cpp");
}

// No timestamps
TEST_CASE("Test CodeLlama-34b-Instruct-prompt1.cpp", "[CodeLlama-34b-Instruct-prompt1]") {
    runTest("CodeLlama-34b-Instruct-prompt1.cpp");
}

// No compile
TEST_CASE("Test CodeLlama-34b-Instruct-prompt2.cpp", "[CodeLlama-34b-Instruct-prompt2]") {
    runTest("CodeLlama-34b-Instruct-prompt2.cpp");
}

// Can't exit
TEST_CASE("Test CodeLlama-34b-Instruct-prompt3.cpp", "[CodeLlama-34b-Instruct-prompt3]") {
    runTest("CodeLlama-34b-Instruct-prompt3.cpp");
}

// Can't exit
TEST_CASE("Test CodeLlama-13b-Instruct-prompt1.cpp", "[CodeLlama-13b-Instruct-prompt1]") {
    runTest("CodeLlama-13b-Instruct-prompt1.cpp");
}

// No compile
TEST_CASE("Test CodeLlama-13b-Instruct-prompt2.cpp", "[CodeLlama-13b-Instruct-prompt2]") {
    runTest("CodeLlama-13b-Instruct-prompt2.cpp");
}

// Can't exit
TEST_CASE("Test CodeLlama-13b-Instruct-prompt3.cpp", "[CodeLlama-13b-Instruct-prompt3]") {
    runTest("CodeLlama-13b-Instruct-prompt3.cpp");
}

// No compile
TEST_CASE("Test CodeLlama-7b-Instruct-prompt1.cpp", "[CodeLlama-7b-Instruct-prompt1]") {
    runTest("CodeLlama-7b-Instruct-prompt1.cpp");
}

// No compile
TEST_CASE("Test CodeLlama-7b-Instruct-prompt2.cpp", "[CodeLlama-7b-Instruct-prompt2]") {
    runTest("CodeLlama-7b-Instruct-prompt2.cpp");
}

// No compile
TEST_CASE("Test CodeLlama-7b-Instruct-prompt3.cpp", "[CodeLlama-7b-Instruct-prompt3]") {
    runTest("CodeLlama-7b-Instruct-prompt3.cpp");
}

// No compile
TEST_CASE("Test Langchain_CodeLlama-13b.cpp", "[Langchain_CodeLlama-13b]") {
    runTest("Langchain_CodeLlama-13b.cpp");
}

