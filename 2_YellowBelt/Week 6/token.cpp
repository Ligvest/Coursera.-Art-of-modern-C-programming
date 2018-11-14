#include "token.h"

#include <stdexcept>

using namespace std;

//date == 2017-07-08
vector<Token> Tokenize(istream& cl) {
  vector<Token> tokens;

  char c;
  while (cl >> c) {
//if Digit
    if (isdigit(c)) {
      string date(1, c);
      for (int i = 0; i < 3; ++i) {
        while (isdigit(cl.peek())) {
          date += cl.get();
        }
        if (i < 2) {
          date += cl.get(); // Consume '-'
        }
      }
      tokens.push_back({date, TokenType::DATE});
//if Quote
    } else if (c == '"') {
      string event;
      getline(cl, event, '"');
      tokens.push_back({event, TokenType::EVENT});
//if "date"
    } else if (c == 'd') {
      if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') {
        tokens.push_back({"date", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
//if "event"
    } else if (c == 'e') {
      if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
          cl.get() == 't') {
        tokens.push_back({"event", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");
      }
//if "AND"
    } else if (c == 'A') {
      if (cl.get() == 'N' && cl.get() == 'D') {
        tokens.push_back({"AND", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
//if "OR"
    } else if (c == 'O') {
      if (cl.get() == 'R') {
        tokens.push_back({"OR", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
//if "("
    } else if (c == '(') {
      tokens.push_back({"(", TokenType::PAREN_LEFT});
//if ")"
    } else if (c == ')') {
      tokens.push_back({")", TokenType::PAREN_RIGHT});
//if "<"
    } else if (c == '<') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({"<=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({"<", TokenType::COMPARE_OP});
      }
    } else if (c == '>') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({">=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({">", TokenType::COMPARE_OP});
      }
//if "=="
    } else if (c == '=') {
      if (cl.get() == '=') {
        tokens.push_back({"==", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    } else if (c == '!') {
      if (cl.get() == '=') {
        tokens.push_back({"!=", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
  }

  //({"date", TokenType::COLUMN}, {"==", TokenType::COMPARE_OP}, {date, TokenType::DATE})
  return tokens;
}
