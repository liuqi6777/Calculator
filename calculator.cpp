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
        printf("[ERROR] Please select a valid mode.\n");
        return INVALID_MODE;
    }
    return SUCCESS;
}


inline static int ops_level(const char op)
{
    switch (op)
    {
        case '#': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        case '^': return 3;
        case '(': return 9;
        case ')': return 9;
        default: return -1;
    }
}

status Calculator::__input_parse(Expression &infixExpr, Mode mode)
{
    int idx = 0;
    // printf("%s\n", str);

    if (mode == BASIC_MODE)
    {
        printf("[INFO] Please input the expression:\n");
        char *str = (char *)malloc((MAX_LEN) * sizeof(char));
        scanf("%s", str);
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
                printf("[ERROR] Invalid operator: \"%c\".\n", *str);
                return INVALID_OPERATOR;
            }
        }
    }

    else if (mode == VARIABLE_MODE)
    {
        char var;
        printf("[INFO] Please input the name of the variable:\n");
        scanf("%c", &var);
        printf("[INFO] Variable name is: %c.\n", var);
        printf("[INFO] Please input the expression:\n");
        char *str = (char *)malloc((MAX_LEN) * sizeof(char));
        scanf("%s", str);
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
                str++;
            }
            else if (*str == var)
            {
                infixExpr.expr[idx].type = VARIABLE;
                idx++;
                str++;
            }
            else if (*str == '\0' || *str == '\n')
            {
                break;
            }
            else
            {
                printf("[ERROR] Invalid operator: \"%c\".\n", *str);
                return INVALID_OPERATOR;
            }
        }
    }

    else if (mode == POLY_MODE)
    {
        char var = 'x';
        char op = '\0';
        char *end;
        Number num;
        while (1)
        {
            Poly p;
            char *str = (char *)malloc((MAX_LEN) * sizeof(char));
            printf("[INFO] Please input a poly:\n");
            scanf("%s", str);
            while (strlen(str) > 0)
            {
                PolyNode pn = new PolyItem;
                num = strtod(str, &end);
                if (str != end) // get a number
                {
                    pn->c = num;
                    str = end;
                    assert(*str == '*');
                    str ++;
                    assert(*str == 'x');
                }
                else if (*str == '-' || *str == '+')
                {
                    pn->c = *str == '-' ? -1 : 1;
                    str ++;
                    assert(*str == 'x');
                }
                else if (*str == 'x')
                    pn->c = 1;
                else
                    break;

                str ++;
                if (*str == '^')
                {
                    str ++;
                    num = strtod(str, &end);
                    pn->power = num;
                    str = end;
                }
                else
                {
                    pn->power = 1;
                    str ++;
                }

                p.insert(pn);
            }
            p.__sort_descending();
            std::cout << p << std::endl;

            infixExpr.expr[idx].type = POLY;
            infixExpr.expr[idx].data.poly = p;
            idx ++;

            getchar();
            printf("[INFO] Please enter an operator:\n");
            scanf("%c", &op);
            // printf("[INFO] Input operator: '%c'\n", op);
            if (ISOPS(op))
            {
                PUT_OP(infixExpr, op, idx);
                idx++;
            }
            else if (op == '=' || op == '#')
            {
                break;
            }
            else
            {
                printf("[ERROR] Invalid operator: \"%c\".\n", op);
                return INVALID_OPERATOR;
            }
        }
    }

    else if (mode == VECTOR_MODE)
    {
        char op = '\0';
        while (1)
        {
            int dim = 0;
            printf("[INFO] Please input the dimension of the vector:\n");
            scanf("%d", &dim);
            Vector v(dim);
            printf("[INFO] Please input the %d elements of the vector:\n", dim);
            for (int i = 0; i < dim; i++)
            {
                Number num;
                scanf("%lf", &num);
                v.put(i, num);
            }

            infixExpr.expr[idx].type = VECTOR;
            infixExpr.expr[idx].data.vec = v;
            idx ++;

            getchar();
            printf("[INFO] Please enter an operator:\n");
            scanf("%c", &op);
            if (ISOPS(op))
            {
                PUT_OP(infixExpr, op, idx);
                idx++;
            }
            else if (op == '=' || op == '#')
            {
                break;
            }
            else
            {
                printf("[ERROR] Invalid operator: \"%c\".\n", op);
                return INVALID_OPERATOR;
            }
        }
    }

    else
    {
        printf("[ERROR] Please select a valid mode.\n");
        return INVALID_MODE;
    }

    infixExpr.length = idx;
    // printf("[INFO] The length of the expression is %d.\n", infixExpr.length);

    return SUCCESS;
}

// 表达式中缀转后缀
status Calculator::__infix2postfix(Expression &infixExpr, Expression &postfixExpr)
{
    printf("[INFO] Infix to postfix...");

    char *stack = new char[infixExpr.length]; // 符号栈
    int top = 0;                  // 栈顶下标
    int len = 0;                  // 后缀表达式长度

    for (size_t i = 0; i < infixExpr.length; i++)
    {

        if (infixExpr.expr[i].type != OPERATOR)
        {
            postfixExpr.expr[len].data = infixExpr.expr[i].data;
            postfixExpr.expr[len].type = infixExpr.expr[i].type;
            len++;
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
                while (top && stack[top-1] != '(' && ops_level(stack[top-1]) >= ops_level(infixExpr.expr[i].data.op)) //栈顶高于等于当前符号
                {
                    // 弹出
                    PUT_OP(postfixExpr, stack[--top], len);
                    len++;
                }
                // 当前符号进栈
                stack[top++] = infixExpr.expr[i].data.op;
                break;
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

    printf("Finished.\n");

    return SUCCESS;
}

// 计算后缀表达式
status Calculator::__calculate(Expression &postfixExpr, ExprItem &result)
{
    ExprItem e[postfixExpr.length];
    ExprItem x1, x2;
    size_t top = 0;
    if (this->mode == VARIABLE_MODE)
    {
        printf("[INFO] Please input the value of the variable:\n");
        Number num;
        scanf("%lf", &num);
        for (size_t i = 0; i < postfixExpr.length; i++)
        {
            if (postfixExpr.expr[i].type == VARIABLE)
            {
                postfixExpr.expr[i].data.num = num;
                postfixExpr.expr[i].type = NUMBER;
            }
        }
    }
    for (size_t i = 0; i < postfixExpr.length; i++)
    {
        if (postfixExpr.expr[i].type != OPERATOR)
        {
            e[top++] = postfixExpr.expr[i];
        }
        else
        {
            char op = postfixExpr.expr[i].data.op;
            x1 = e[--top];
            x2 = e[--top];
            switch (op)
            {
            case '+':
                e[top++] = x1 + x2;
                break;
            case '-':
                e[top++] = x2 - x1;
                break;
            case '*':
                e[top++] = x1 * x2;
                break;
            case '/':
                // TODO: check type
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

// -----------------
// 1. 输入计算器模式
// 2. 输入表达式并计算
// 3. 退出
void Calculator::run()
{
    printf("==========================================\n");
    printf("[INFO] Please enter a number to select a mode:\n");
    printf("[1]: Basic Mode\n");
    printf("[2]: Variable Mode\n");
    printf("[3]: Polynomial Mode\n");
    printf("[4]: Vector Mode\n");
    int mode;
    status s;
    scanf("%d", &mode);
    getchar();
    s = set_mode(mode);
    if (s) __exit(s);
    // input();
    Expression e, e2;
    ExprItem res;
    s = __input_parse(e, this->mode);
    if (s) __exit(s);
    s = __infix2postfix(e, e2);
    if (s) __exit(s);
    s = __calculate(e2, res);
    if (s) __exit(s);

    printf("[RESULT] The result of the expression is: ");
    std::cout << res << std::endl;
    __exit(SUCCESS);
}
