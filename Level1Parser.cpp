#include "Level1Parser.h"
#include <iostream>

bool IsNewLineSymbol(char s);
bool IsBlankSymbol(char s);
bool IsBraceSymbol(char s);
bool IsOpeningBrace(char s);
bool IsClosingBrace(char s);
bool IsNameTrackingStopSymbol(char s);

namespace Level1Parser {

list<Level1Token> Parse(const string &s_expr) { // TODO is it ok to return list like this?
    list<Level1Token> result;
    int identifier_starting_pos = -1;
    int brace_cntr = 0;

    for (int i = 0; i < s_expr.length(); i++) {
        char symb = s_expr.at(i);
        if (IsNameTrackingStopSymbol(symb)) {
            if (identifier_starting_pos != -1) {
                int length = i - identifier_starting_pos;
                result.push_back(Level1Token(s_expr.substr(identifier_starting_pos, length)));
                identifier_starting_pos = -1;
            }
        } else {
            if (identifier_starting_pos == -1) {
                identifier_starting_pos = i;
            }
        }
        if (IsBraceSymbol(symb)) {
            result.push_back(Level1Token(symb));
            if (IsOpeningBrace(symb)) brace_cntr++;
            if (IsClosingBrace(symb)) brace_cntr--;
            if (brace_cntr < 0) {
                throw WrongAmountOfBraces( "String \"" + s_expr + "\"\n" +
                        "Excess of closing braces, possible position: " + to_string(i));
            }
            continue;
        }
    }

    if (brace_cntr > 0) {
        throw WrongAmountOfBraces("Excess of opening braces");
    }
    if (brace_cntr < 0) {
        throw WrongAmountOfBraces("Excess of closing braces");
    }

    // Suppose we want to parse just "foo", then we will exit previous cycle
    // before putting token to list.
    // So after exiting cycle we must to check if
    // name_starting_pos -1 or not and if not, then that means we started to
    // record something and didn't finished it
    if (identifier_starting_pos != -1) {
        result.push_back(Level1Token(s_expr.substr(identifier_starting_pos, s_expr.length())));
    }

    return result;
}

void Print(list<Level1Token> tokens) {
    list<Level1Token>::iterator it;
    cout << "..." << endl;
    int i = 0;
    for (it = tokens.begin(); it != tokens.end(); ++it, i++) {
        cout << "Token " << i << ": \"" << it->get_content() << "\"" << endl;
    }
}

} // namespace Level1Parser

bool IsNewLineSymbol(char s) {
    return s == '\n';
}

bool IsBlankSymbol(char s) {
    return s == ' ' || s == '\t' || IsNewLineSymbol(s);
}

bool IsBraceSymbol(char s) {
    return IsOpeningBrace(s) || IsClosingBrace(s);
}

bool IsOpeningBrace(char s) {
    return s == '(';
}

bool IsClosingBrace(char s) {
    return s == ')';
}

bool IsNameTrackingStopSymbol(char s) {
    return IsBlankSymbol(s) || IsBraceSymbol(s);
}
