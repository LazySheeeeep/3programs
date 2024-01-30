#include "calculator.hpp"
#include <stack>

int Calculator::operator()(string &input) {
  size_t current_index = 0;
  stack<int> nums;
  stack<TokenType> ops;

  Token token = next_token(input, current_index);

  while (token.type != END) {
    if (token.type == NUMBER) {
      nums.push(token.value);
    } else {
      while (!ops.empty() && ops.top() >= token.type) {
        int num2 = nums.top();
        nums.pop();
        int num1 = nums.top();
        nums.pop();

        TokenType op = ops.top();
        ops.pop();

        nums.push(binary_calculate(num1, num2, op));
      }
      ops.push(token.type);
    }

    token = next_token(input, current_index);
  }

  while (!ops.empty()) {
    int num2 = nums.top();
    nums.pop();
    int num1 = nums.top();
    nums.pop();

    TokenType op = ops.top();
    ops.pop();

    nums.push(binary_calculate(num1, num2, op));
  }

  return nums.top();
}

Token Calculator::next_token(string &input, size_t &current_index) {
  while (current_index < input.size()) {
    char current_char = input[current_index];

    if (isdigit(current_char)) {
      string number = "";
      while (current_index < input.size() && isdigit(input[current_index])) {
        number += input[current_index];
        current_index++;
      }
      return {NUMBER, stoi(number)};
    } else if (current_char == '+') {
      current_index++;
      return {ADD, 0};
    } else if (current_char == '*') {
      current_index++;
      return {MULT, 0};
    } else if (isspace(current_char)) {
      current_index++;
    } else {
      throw "Invalid character";
    }
  }

  return {END, 0};
}

int Calculator::binary_calculate(int num1, int num2, TokenType op) {
  if (op == ADD) {
    return num1 + num2;
  } else if (op == MULT) {
    return num1 * num2;
  }

  throw "Invalid operator";
}
