//
// Created by Eason Lee on 10/30/2015.
//

#ifndef EXTENDEDCAL_AST_H
#define EXTENDEDCAL_AST_H

#include <iostream>


using namespace std;

// define all the class we need
class Expression;
class Value;
class UnaryExpression;
class BinaryExpression;
class NegationExpression;
class PositiveExpression;
class NotExpression;
class BinaryExpression;
class AdditionExpression;
class SubtractionExpression;
class MultiplicationExpression;
class DivisionExpression;
class ModExpression;
class LogicalOrExpression;
class LogicalAndExpression;
class EqualExpression;
class NotEqualExpression;
class GreaterThanExpression;
class LessThanExpression;
class GreaterThanEqualExpression;
class LessThanEqualExpression;

class Look {
public:
    virtual void use(Expression *) = 0;
    virtual void use(Value *) = 0;
    virtual void use(UnaryExpression *) = 0;
    virtual void use(BinaryExpression *) = 0;
    virtual void use(NegationExpression *) = 0;
    virtual void use(PositiveExpression *) = 0;
    virtual void use(NotExpression *) = 0;
    virtual void use(AdditionExpression *) = 0;
    virtual void use(SubtractionExpression *) = 0;
    virtual void use(MultiplicationExpression *) = 0;
    virtual void use(DivisionExpression *) = 0;
    virtual void use(ModExpression *) = 0;
    virtual void use(LogicalOrExpression *) = 0;
    virtual void use(LogicalAndExpression *) = 0;
    virtual void use(EqualExpression *) = 0;
    virtual void use(NotEqualExpression *) = 0;
    virtual void use(GreaterThanExpression *) = 0;
    virtual void use(LessThanExpression *) = 0;
    virtual void use(GreaterThanEqualExpression *) = 0;
    virtual void use(LessThanEqualExpression *) = 0;
};      //class "look" is just like the intermediate panel to control all the call

// the below is to build the abstract syntax tree, generally three basic class, Expr, Unary, Binary
class Looknode {
    virtual void accept(Look *) = 0;
};

class Expression : public Looknode {
public:
    void accept(Look * v) {}
    virtual int evaluate() const = 0;
};


class Value : public Expression, Looknode {
public:
    Value(int val) : mValue(val) {}
    Value(bool val) : mValue(val ? 1 : 0) {}
    void accept(Look * v) {
        v->use(this);
    }
    int evaluate() const {
        return mValue;
    }

private:
    int mValue;
};

class UnaryExpression : public Expression, Looknode {
public:
    UnaryExpression(Expression * l) : mExpr(l) {}
    Expression * getExpression() const {
        return mExpr;
    }
    void accept(Look * v) {}
protected:
    Expression * mExpr;
};

class BinaryExpression : public Expression, Looknode {
public:
    BinaryExpression(Expression * l, Expression * r) : mLeft(l), mRight(r) {}
    Expression * getLeft() const {
        return mLeft;
    }
    Expression * getRight() const {
        return mRight;
    }
    void accept(Look * v) {}
protected:
    Expression * mLeft;
    Expression * mRight;
};

class NegationExpression : public UnaryExpression, Looknode {
public:
    NegationExpression(Expression * val) : UnaryExpression(val) {}
    int evaluate() const {
        return -mExpr->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class PositiveExpression : public UnaryExpression, Looknode {
public:
    PositiveExpression(Expression * val) : UnaryExpression(val) {}
    int evaluate() const {
        return +mExpr->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class NotExpression : public UnaryExpression, Looknode {
public:
    NotExpression(Expression * val) : UnaryExpression(val) {}
    int evaluate() const {
        bool val = (mExpr->evaluate() != 0);
        return !val;
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class AdditionExpression : public BinaryExpression, Looknode {
public:
    AdditionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
    int evaluate() const {
        return mLeft->evaluate() + mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class SubtractionExpression : public BinaryExpression, Looknode {
public:
    SubtractionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
    int evaluate() const {
        return mLeft->evaluate() - mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class MultiplicationExpression : public BinaryExpression, Looknode {
public:
    MultiplicationExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
    int evaluate() const {
        return mLeft->evaluate() * mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class DivisionExpression : public BinaryExpression, Looknode {
public:
    DivisionExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
    int evaluate() const {
        return mLeft->evaluate() / mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class ModExpression : public BinaryExpression, Looknode {
public:
    ModExpression(Expression * l, Expression * r) : BinaryExpression(l, r) { }
    int evaluate() const {
        return mLeft->evaluate() % mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class LogicalOrExpression : public BinaryExpression, Looknode {
public:
    LogicalOrExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        bool lhs = (mLeft->evaluate() != 0);
        bool rhs = (mRight->evaluate() != 0);
        return lhs || rhs;
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class LogicalAndExpression : public BinaryExpression, Looknode {
public:
    LogicalAndExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        bool lhs = (mLeft->evaluate() != 0);
        bool rhs = (mRight->evaluate() != 0);
        return lhs && rhs;
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class EqualExpression : public BinaryExpression, Looknode {
public:
    EqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() == mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class NotEqualExpression : public BinaryExpression, Looknode {
public:
    NotEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() != mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class GreaterThanExpression : public BinaryExpression, Looknode {
public:
    GreaterThanExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() > mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class LessThanExpression : public BinaryExpression, Looknode {
public:
    LessThanExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() < mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class GreaterThanEqualExpression : public BinaryExpression, Looknode {
public:
    GreaterThanEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() >= mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

class LessThanEqualExpression : public BinaryExpression, Looknode {
public:
    LessThanEqualExpression(Expression * l, Expression * r) : BinaryExpression(l, r) {}
    int evaluate() const {
        return mLeft->evaluate() <= mRight->evaluate();
    }
    void accept(Look * v) {
        v->use(this);
    }
};

// the specific implementation of the class "Look"
class EvaluateLook : public Look {
    void use(Expression *val) {}
    void use(UnaryExpression * val) {}
    void use(BinaryExpression * val) {}

    void use(Value * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(NegationExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(PositiveExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(AdditionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(SubtractionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(MultiplicationExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(DivisionExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(ModExpression * val) {
        std::cout << val->evaluate() << std::endl;
    }

    void use(LogicalOrExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(LogicalAndExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(EqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(NotEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(GreaterThanExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(LessThanExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(GreaterThanEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(LessThanEqualExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
    void use(NotExpression * val) {
        std::cout << ((val->evaluate()) ? "true" : "false") << std::endl;
    }
};

#endif //EXTENDEDCAL_AST_H
