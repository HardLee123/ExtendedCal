//
// Created by Eason Lee on 10/30/2015.
//

#ifndef EXTENDEDCAL_PARSER_H
#define EXTENDEDCAL_PARSER_H

#include <vector>
#include "AST.h"
#include "Lexer.h"

class Parser {
public:
    Parser(std::vector<Token> tokens) : TokenList(tokens), CurrentIndex(0) {}
    Expression * Parse();
private:
    std::vector<Token> TokenList;
    Token mLookAhead;
    int CurrentIndex;

    void next();
    Expression * expression();
    Expression * logicalOrExpr();
    Expression * logicalAndExpr();
    Expression * equalityExpr();
    Expression * orderingExpr();
    Expression * additiveExpr();
    Expression * multiplicativeExpr();
    Expression * unaryExpr();
    Expression * primaryExpr();
};


#endif //EXTENDEDCAL_PARSER_H
