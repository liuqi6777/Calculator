#ifndef CALCULATOR
#define CALCULATOR

#include "expression.h"


#define ISDIGIT(x) (x >= '0' && x <= '9')
#define ISOPS(x) ( \
    x == '+' || \
    x == '-' || \
    x == '*' || \
    x == '/' || \
    x == '^' || \
    x == '(' || \
    x == ')' || \
    x == '#')


class Calculator
{
public:
    Calculator() : mode(BASIC_MODE) {};
    ~Calculator() {};

    status input();
    status set_mode();
    status calculate(Expression &Expr, ExprItem &result);

    void run();

private:
    Mode mode;

    status __input_parse(Expression &infixExpr, Mode mode);
    status __infix2postfix(Expression &infixExpr, Expression &postfixExpr);
    status __calculate(Expression &Expr, ExprItem &result);

    void __exit(status s) { exit(s); }
};


#endif // CALCULATOR