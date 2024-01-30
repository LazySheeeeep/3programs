#include <cstring>
#include <string>

using namespace std;

enum TokenType { NUMBER, ADD, MULT, END };

struct Token {
  TokenType type;
  int value;
};

class Calculator {
public:
  int operator()(string &);

private:
  Token next_token(string &input, size_t &current_index);

  int binary_calculate(int num1, int num2, TokenType op);
};
