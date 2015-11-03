//
// Created by Eason Lee on 10/30/2015.
//

#ifndef EXTENDEDCAL_LEXER_H
#define EXTENDEDCAL_LEXER_H


#include <string>
#include <vector>
#include <stdexcept>

enum TokenType {
    LETTER,     // [a-z][A-Z]
    NUMBER,     // [-MAX INT, +MAX INT]
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    LT,         // <
    GT,         // >
    EQUAL,      // ==
    LTE,        // <=
    GTE,        // >=
    NEQ,        // !=
    NOT,        // !
    AND,        // &&
    OR,         // ||
    TRUE,       // boolean value true
    FALSE,      // boolean value false
    WHITESPACE, // Whitespace
    LPAREN,     // (
    RPAREN,     // )
    NONE        // A token with no type
};


// A token consists of the type
// and its value
class Token {
public:
    Token() : tokentype(NONE), TokenContent("") {}
    Token(TokenType type, std::string text) : tokentype(type), TokenContent(text) {}
    TokenType getType() const;
    std::string * getText();
private:
    TokenType tokentype;
    std::string TokenContent;
};

class Lexer {
public:
    Lexer(std::istream & input);
    std::vector<Token> Lex();
private:
    std::vector<Token> TokenLists;
    std::istream &WholeInputStream;
};
#endif //EXTENDEDCAL_LEXER_H
