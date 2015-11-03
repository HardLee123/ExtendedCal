#include <iostream>
#include "AST.h"
#include "Lexer.h"
#include "Parser.h"
#include <sstream>

using namespace std;

int main() {
    string line;
    getline(cin, line);
    stringstream numbersting (line);
    Lexer l = Lexer(numbersting);
    vector<Token> tokens;

    tokens = l.Lex();
    Parser p = Parser(tokens);
    Expression * expr = p.Parse();


    EvaluateLook * visitor = new EvaluateLook();


    expr->accept(visitor);
    cout << endl;


    return 0;
}

