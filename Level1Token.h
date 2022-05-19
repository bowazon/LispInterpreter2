#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum Level1TokenType {
    kOpeningBrace = 0,
    kClosingBrace,
    kIdentifier
};

class Level1Token {
private:
    Level1TokenType token_type;
    string content;

    Level1Token() {
        // Token can't be created without string content
    };

    void FigureOutType() {
        if (content.compare("(") == 0) token_type = kOpeningBrace;
        else if (content.compare(")") == 0) token_type = kClosingBrace;
        else token_type = kIdentifier;
    }

public:
    Level1Token(string content) {
        this->content = content;
        FigureOutType();
    }
    Level1Token(char content) {
        this->content = string(1, content);
        FigureOutType();
    }
    Level1TokenType get_type() {
        return this->token_type;
    }
    string get_content() {
        return this->content;
    }
};

#endif // TOKEN_H
