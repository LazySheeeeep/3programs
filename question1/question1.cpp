#include "calculator.hpp"
#include <iostream>

int N = 8;
string nums[4]{"1", "2", "3", "5"};
char ops[2]{'+', '*'};

Calculator calculate;

void loop_test(string &expression, int remainder_count) {
  if (remainder_count == 0)
    return;
  for (char op : ops) {
    expression.push_back(op);
    for (const string &num : nums) {
      expression += num;
      if (calculate(expression) == N)
        cout << expression << endl;
      loop_test(expression, remainder_count - 1);
      expression.erase(expression.rfind(num), num.size());
    }
    expression.pop_back();
  }
}

int main(int argc, char *argv[]) {
  int L = 5;
  for (int i = 1; i < argc; i += 2) {
    if (i + 1 < argc) {
      if (strcmp(argv[i], "-x") == 0) {
        nums[2] = argv[i + 1];
      } else if (strcmp(argv[i], "-y") == 0) {
        nums[3] = argv[i + 1];
      } else if (strcmp(argv[i], "-N") == 0 || strcmp(argv[i], "-n") == 0) {
        N = std::atoi(argv[i + 1]);
      } else if (strcmp(argv[i], "-L") == 0 || strcmp(argv[i], "-l") == 0) {
        L = std::atoi(argv[i + 1]);
      } else {
        std::cerr << "Invalid argument: " << argv[i] << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Missing value for argument: " << argv[i] << std::endl;
      return 1;
    }
  }
  L--;
  if (L == 1) {
    for (auto num : nums) {
      if (calculate(num) == N)
        cout << num << endl;
    }
    return 0;
  }
  string expression = "";
  for (auto num : nums) {
    expression = num;
    loop_test(expression, L - 1);
  }
  return 0;
}
