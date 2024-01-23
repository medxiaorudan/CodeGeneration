  #include <iostream>
  #include <vector>
  #include <algorithm>
  #include <ctime>

  using namespace std;

  int main() {
      vector<int> numbers;
      int number;

      while (cin >> number) {
          numbers.push_back(number);
      }

      sort(numbers.begin(), numbers.end());

      for (int i = 0; i < numbers.size(); i++) {
          cout << numbers[i] << " ";
      }

      return 0;
  }
