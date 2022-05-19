#ifndef LEVEL1PARSER_H
#define LEVEL1PARSER_H

#include "Level1Token.h"
#include <string>
#include <list>

using namespace std;

namespace Level1Parser {
    // Example: "(+ abc (* 3 5 ) )  " will be parsed to tokens "(", "+",
    // "abc", "(", "*", "3", "5", ")", ")". All blank symbols will be ignored.
    list<Level1Token> Parse(const string &s_expr);
    void Print(list<Level1Token> tokens);

    // TODO Do we really need this exception? Without building
    // syntax tree we can just count braces and if error occurred
    // we wouldn't be able to find out where trouble happened precisely
    class WrongAmountOfBraces : exception {
    private:
        string msg;
    public:
        WrongAmountOfBraces(string msg) {
            this->msg = msg;
        }
        string get_msg() {
            return msg;
        }
    };
}

#endif // LEVEL1PARSER_H
