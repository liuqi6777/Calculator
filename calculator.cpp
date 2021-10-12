#include "calculator.h"

#define PUT_NUM(Expr, x, idx)         \
    do                                \
    {                                 \
        Expr.expr[idx].type = NUMBER; \
        Expr.expr[idx].data.num = x;  \
    } while (0)

#define PUT_OP(Expr, x, idx)            \
    do                                  \
    {                                   \
        Expr.expr[idx].type = OPERATOR; \
        Expr.expr[idx].data.op = x;     \
    } while (0)

Calculator::Calculator()
{
    this->rawExpression = new char[MAX_LEN];
    this->mode = BASIC_MODE;
}

Calculator::~Calculator()
{
    // delete[] this->rawExpression;
    // delete[] this->thisExpression;
    // delete[] this->lastExpression;
    // delete[] this->lastResult;
}

status Calculator::set_mode(int mode)
{
    switch (mode)
    {
    case 1:
        this->mode = BASIC_MODE;
        printf("[INFO] Switch to the basic mode.\n");
        break;
    case 2:
        this->mode = VARIABLE_MODE;
        printf("[INFO] Switch to the variable mode.\n");
        break;
    case 3:
        this->mode = POLY_MODE;
        printf("[INFO] Switch to the polynomial mode.\n");
        break;
    case 4:
        this->mode = VECTOR_MODE;
        printf("[INFO] Switch to the vector mode.\n");
        break;
    default:
        printf("[INFO] Please select a valid mode.\n");
        return INVALID_MODE;
    }
    return SUCCESS;
}

status Calculator::input()
{
    printf("[INFO] Please input the expression:\n");
    switch (this->mode)
    {
    case BASIC_MODE:
        // gets(this->rawExpression);
        scanf("%s", this->rawExpression);
        break;
    }
    return SUCCESS;
}

inline static int ops_level(const char op)
{
    switch (op)
    {
    case '#':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '%':
        return 2;
    case '(':
        return 9;
    case ')':
        return 9;
    default:
        return -1;
    }
}

status Calculator::__parse(const char *raw, Expression &infixExpr, Mode mode, const char *var)
{
    size_t n = strlen(raw);
    char *str = (char *)malloc((n + 1) * sizeof(char));
    strcpy(str, raw);
    int idx = 0;
    // printf("%s\n", str);

    if (mode == BASIC_MODE)
    {
        char *end;
        Number num;
        while (strlen(str) > 0)
        {
            while (*str == ' ')
                str++;
            if (ISDIGIT(*str))
            {
                num = strtod(str, &end);
                str = end;
                PUT_NUM(infixExpr, num, idx);
                idx++;
                // std::cout << " *" << num << "* ";
            }
            else if (ISOPS(*str))
            {
                char op = *str;
                PUT_OP(infixExpr, op, idx);
                idx++;
                // std::cout << "**" << *str << "**";
                str++;
            }
            else if (*str == '\0' || *str == '\n')
                break;
            else
            {
                printf("[INFO] Invalid operator: \"%c\".\n", *str);
                return INVALID_OPERATOR;
            }
        }
    }

    else if (mode == VARIABLE_MODE)
    {
        printf("[INFO] Variable name is: %s.\n", var);
    }

    else if (mode == POLY_MODE)
    {
    }

    else if (mode == VECTOR_MODE)
    {
    }

    else
    {
        printf("[INFO] Please select a valid mode.\n");
        return INVALID_MODE;
    }

    infixExpr.length = idx;

    return SUCCESS;
}

// 表达式中缀转后缀
// 要求：输入的是合法表达式；若是带变量的表达式，需要给变量赋值
status Calculator::__infix2postfix(Expression &infixExpr, Expression &postfixExpr)
{
    // todo 内存分配

    char *stack = new char[infixExpr.length]; // 符号栈
    int top = 0;                 // 栈顶下标
    int len = 0;                  // 后缀表达式长度

    for (size_t i = 0; i < infixExpr.length; i++)
    {

        if (infixExpr.expr[i].type == NUMBER)
        {
            postfixExpr.expr[len].data.num = infixExpr.expr[i].data.num;
            postfixExpr.expr[len].type = NUMBER;
            len++;
        }
        else if (infixExpr.expr[i].type == VARIABLE)
        {
        }
        else if (infixExpr.expr[i].type == POLY)
        {
        }
        else if (infixExpr.expr[i].type == VECTOR)
        {
        }
        else if (infixExpr.expr[i].type == OPERATOR)
        {

            switch (infixExpr.expr[i].data.op)
            {
            case '(':
                stack[top++] = '(';
                break;
            case ')':
                while (stack[top-1] != '(')
                { // 持续出栈至'('
                    PUT_OP(postfixExpr, stack[--top], len);
                    len++;
                }
                top--;
                break;

            case '+':
            case '-':
            case '*':
            case '/':
                while (top > 0 && ops_level(stack[top]) >= ops_level(infixExpr.expr[i].data.op)) //栈顶高于等于当前符号
                {
                    // 弹出
                    PUT_OP(postfixExpr, stack[--top], len);
                    len++;
                }
                // 当前符号进栈
                stack[top++] = infixExpr.expr[i].data.op;
                break;
            default:
                return INVALID_OPERATOR;
            }
        }
    }
    while (top > 0)
    {
        // 剩下所有符号出栈
        PUT_OP(postfixExpr, stack[--top], len);
        len++;
    }
    postfixExpr.length = len;
    delete[] stack;

    return SUCCESS;
}

// 计算后缀表达式
status Calculator::__calculate(Expression &postfixExpr, ExprItem &result)
{
    ExprItem e[postfixExpr.length];
    ExprItem x1, x2;
    size_t top = 0;
    for (size_t i = 0; i < postfixExpr.length; i++)
    {
        if (postfixExpr.expr[i].type != OPERATOR)
        {
            e[top++] = postfixExpr.expr[i];
        }
        else
        {
            char op = postfixExpr.expr[i].data.op;
            switch (op)
            {
            case '+':
                x1 = e[--top];
                x2 = e[--top];
                e[top++] = x1 + x2;
                break;
            case '-':
                x1 = e[--top];
                x2 = e[--top];
                e[top++] = x1 - x2;
                break;
            case '*':
                x1 = e[--top];
                x2 = e[--top];
                e[top++] = x1 * x2;
                break;
            case '/':
                // TODO: check type
                // x1 = e[--top];
                // x2 = e[--top];
                // e[top++] = x1 / x2;
            default:
                printf("[INFO] Invalid operator: \"%c\".\n", op);
                return INVALID_OPERATOR;
            }
        }
    }
    result = e[--top];
    return SUCCESS;
}

// -------------------------------------------------------------------------------------------------
// 1. 输入计算器模式
// 2. 输入表达式并计算
// 3. 退出
void Calculator::run()
{
    printf("==========================================\n");
    printf("Please enter a number to select a mode:\n");
    printf("[1]: Basic Mode\n");
    printf("[2]: Variable Mode\n");
    printf("[3]: Polynomial Mode\n");
    printf("[4]: Vector Mode\n");
    int mode;
    scanf("%d", &mode);
    set_mode(mode);
    input();
    Expression e, e2;
    ExprItem res;
    __parse(rawExpression, e, this->mode);
    __infix2postfix(e, e2);
    __calculate(e2, res);

    printf("[RESULT] The result of the expression is: ");
    std::cout << res << std::endl;
}
