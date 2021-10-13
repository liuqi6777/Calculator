#ifndef CALCULATOR
#define CALCULATOR

#include "expression.h"


#define ISDIGIT(x) (x >= '0' && x <= '9')
#define ISOPS(x) (x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')' || x == '#')


class Calculator
{
public:
    Calculator();
    ~Calculator();

    status input();
    status set_mode(int mode);

    status calculate(Expression &Expr, ExprItem &result);

    void run();

private:
    Mode mode;

    status __input_parse(Expression &infixExpr, Mode mode);
    status __infix2postfix(Expression &infixExpr, Expression &postfixExpr);
    status __calculate(Expression &Expr, ExprItem &result);

    void __exit() { exit(0); }
};


#endif // CALCULATOR