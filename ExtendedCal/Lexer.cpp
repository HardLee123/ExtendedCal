//
// Created by Eason Lee on 10/30/2015.
//
#include "Lexer.h"

#include <istream>
#include <sstream>

Lexer::Lexer(std::istream & input) : WholeInputStream(input) { }//constructor

std::vector<Token> Lexer::Lex() {
    char current;
    while (!WholeInputStream.eof()) {       //eof() is included in <istream>, to check the end of the file
        WholeInputStream.get(current);
        if (isdigit(current)) {
            std::stringstream numberstring;
            while (isdigit(current) && !WholeInputStream.eof()) {
                numberstring << current;
                if (!isdigit(WholeInputStream.peek()))// peek is to look the next character
                    break;
                WholeInputStream.get(current);
            }
            Token t = Token(TokenType::NUMBER, numberstring.str());
            TokenLists.push_back(t);
        } else if (current == ' ') {
            Token t = Token(TokenType::WHITESPACE, " ");
            TokenLists.push_back(t);
        } else if (current == '>') {
            if (WholeInputStream.peek() == '=') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::GTE, ">=");
                TokenLists.push_back(t);
            } else {
                Token t = Token(TokenType::GT, ">");
                TokenLists.push_back(t);
            }
        } else if (current == '<') {
            if (WholeInputStream.peek() == '=') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::LTE, "<=");
                TokenLists.push_back(t);
            } else {
                Token t = Token(TokenType::LT, "<");
                TokenLists.push_back(t);
            }
        } else if (current == '=') {
            if (WholeInputStream.peek() == '=') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::EQUAL, "==");
                TokenLists.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == 't') {            // make suer your input match "true"
            char judgeTrue[4];
            judgeTrue[0] = 't';
            long pos = WholeInputStream.tellg();// tellg(), tell you the current position of pointer
            judgeTrue[1] = (char) WholeInputStream.peek();
            WholeInputStream.seekg(pos + 1);
            judgeTrue[2] = (char) WholeInputStream.peek();
            WholeInputStream.seekg(pos + 2);
            judgeTrue[3] = (char) WholeInputStream.peek();
            if ((judgeTrue[0] == 't' || judgeTrue[0] == 'T')  && judgeTrue[1] == 'r' && judgeTrue[2] == 'u' && judgeTrue[3] == 'e') {
                Token t = Token(TokenType::TRUE, "true");
                TokenLists.push_back(t);
                WholeInputStream.seekg(pos + 3);
            } else {
                // Could be a variable name, or something else...but not in this language
            }
        } else if (current == 'f') {
            char judgeFalse[5];
            judgeFalse[0] = 'f';
            long pos = WholeInputStream.tellg();
            judgeFalse[1] = (char) WholeInputStream.peek();
            WholeInputStream.seekg(pos + 1);
            judgeFalse[2] = (char) WholeInputStream.peek();
            WholeInputStream.seekg(pos + 2);
            judgeFalse[3] = (char) WholeInputStream.peek();
            WholeInputStream.seekg(pos + 3);
            judgeFalse[4] = (char) WholeInputStream.peek();
            if ((judgeFalse[0] == 'f' || judgeFalse[0] == 'F') && judgeFalse[1] == 'a' && judgeFalse[2] == 'l' && judgeFalse[3] == 's' && judgeFalse[4] == 'e') {
                Token t = Token(TokenType::FALSE, "false");
                TokenLists.push_back(t);
                WholeInputStream.seekg(pos + 3);
            } else {
                // Could be a variable name, or something else...but not in this language
            }
        } else if (current == '!') {
            if (WholeInputStream.peek() == '=') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::NEQ, "!=");
                TokenLists.push_back(t);
            } else {
                Token t = Token(TokenType::NOT, "!");
                TokenLists.push_back(t);
            }
        } else if (current == '&') {
            if (WholeInputStream.peek() == '&') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::AND, "&&");
                TokenLists.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == '|') {
            if (WholeInputStream.peek() == '|') {
                WholeInputStream.get(current);
                Token t = Token(TokenType::OR, "||");
                TokenLists.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == '+') {
            Token t = Token(TokenType::PLUS, "+");
            TokenLists.push_back(t);
        } else if (current == '-') {
            Token t = Token(TokenType::MINUS, "-");
            TokenLists.push_back(t);
        } else if (current == '*') {
            Token t = Token(TokenType::MULTIPLY, "*");
            TokenLists.push_back(t);
        } else if (current == '/') {
            Token t = Token(TokenType::DIVIDE, "/");
            TokenLists.push_back(t);
        } else if (current == '%') {
            Token t = Token(TokenType::MOD, "%");
            TokenLists.push_back(t);
        } else if (current == '(' || current == ')') {
            switch (current) {
                case '(':
                    TokenLists.push_back(Token(TokenType::LPAREN, "("));
                    break;
                case ')':
                    TokenLists.push_back(Token(TokenType::RPAREN, ")"));
                    break;
            }
        }
    }
    return TokenLists;
}

TokenType Token::getType() const {
    return tokentype;
}

std::string * Token::getText() {
    return &TokenContent;
}
