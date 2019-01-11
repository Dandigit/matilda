// This file was automatically generated.
// "See generate.py" for details.

#ifndef ENACT_STMT_H
#define ENACT_STMT_H

#include "Expr.h"

class Stmt {
public:
    class Expression;
    class Variable;

    template <class R>
    class Visitor {
    public:
        virtual R visitExpressionStmt(Expression stmt);
        virtual R visitVariableStmt(Variable stmt);
    };

    virtual std::string accept(Stmt::Visitor<std::string> *visitor) = 0;
    virtual void accept(Stmt::Visitor<void> *visitor) = 0;
};

class Stmt::Expression : public Stmt {
public:
    std::shared_ptr<Expr> expr;

    Expression(std::shared_ptr<Expr> expr) : 
        expr{expr} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitExpressionStmt(*this);
    }
};

class Stmt::Variable : public Stmt {
public:
    Token name;
    std::shared_ptr<Expr> initializer;
    bool isConst;

    Variable(Token name,std::shared_ptr<Expr> initializer,bool isConst) : 
        name{name},initializer{initializer},isConst{isConst} {}

    std::string accept(Stmt::Visitor<std::string> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }

    void accept(Stmt::Visitor<void> *visitor) override {
        return visitor->visitVariableStmt(*this);
    }
};

#endif // ENACT_STMT_H
