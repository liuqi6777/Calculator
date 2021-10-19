#ifndef CALCULATION_EXPRESSION_
#define CALCULATION_EXPRESSION_

#include"expression.h"

class Calculation : public Expression 
{
public:
    Calculation();
    Calculation(const string &raw);
    Calculation(const Calculation &other);
    ~Calculation();

    status input();
    status output();
    status parse();
    Number parse(string str);

    Number get_value() const;

    Calculation& operator=(const Calculation &other);
    Calculation operator+(const Calculation &other);
    Calculation operator-(const Calculation &other);
    Calculation operator*(const Calculation &other);

    friend std::ostream& operator<<(std::ostream &out, Calculation &obj);
    friend std::istream& operator>>(std::istream &in, Calculation &obj);

private:
    string raw;
    Number value;

};

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

Calculation::Calculation()
{

}

Calculation::Calculation(const std::string &raw)
{
    this->raw = raw;
    parse();
}

Calculation::Calculation(const Calculation &other)
{
    this->raw = other.raw;
    this->value = other.value;
}

Calculation::~Calculation()
{

}

status Calculation::input()
{   
    std::cout << "[INFO] Please input the expression:" << std::endl;
    getline(std::cin, raw);
    return SUCCESS;
}

status Calculation::output()
{
    std::cout << "[RESULT] The rusult is : " << this->value << "." << std::endl;
    return SUCCESS;
}

status Calculation::parse()
{
    this->value = parse(this->raw);
    return SUCCESS;
}

Number Calculation::parse(string str)
{
    const size_t len = str.length();
    string infix[len];
    string postfix[len];
    size_t pos = 0, idx = 0;
    Number num;
    while (str.length() > 0)
    {
        if (ISDIGIT(str[0]))
        {
            num = stod(str, &pos);
            infix[idx++] = str.substr(0, pos);
            str = str.substr(pos);
        }
        else if (ISOPS(str[0]))
        {
            infix[idx++] = str[0];
            str = str.substr(1);
        }
        // else if (str[0] == '\0' || str[0] == '\n')
        //     break;
        else
        {
            printf("[ERROR] Invalid operator: \"%c\".\n", str[0]);
            return INVALID_OPERATOR;
        }
    }
    size_t infix_len = idx;

    char stack[infix_len]; // 符号栈
    int top = 0;                 // 栈顶下标
    idx = 0;

    for (size_t i = 0; i < infix_len; i++)
    {
        if (ISDIGIT(infix[i][0])) // num
        {
            postfix[idx++] = infix[i];
        }
        else
        {
            switch (infix[i][0])
            {
            case '(':
                stack[top++] = '(';
                break;
            case ')':
                while (stack[top-1] != '(')
                { // 持续出栈至'('
                    postfix[idx++] = stack[--top];
                }
                top--;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (top && stack[top-1] != '(' && ops_level(stack[top-1]) >= ops_level(infix[i][0])) //栈顶高于等于当前符号
                {
                    // 弹出
                    postfix[idx++] = stack[--top];
                }
                // 当前符号进栈
                stack[top++] = infix[i][0];
                break;
            }
        }
    }
    while (top > 0)
    {
        // 剩下所有符号出栈
        postfix[idx++] = stack[--top];
    }
    size_t postfix_len = idx;

    Number nums[postfix_len];
    Number x1, x2;

    top = 0;

    for (size_t i = 0; i < postfix_len; i++)
    {
        if (ISDIGIT(postfix[i][0]))
        {
            nums[top++] = stod(postfix[i], &pos);;
        }
        else
        {
            char op = postfix[i][0];
            x1 = nums[--top];
            x2 = nums[--top];
            switch (op)
            {
            case '+':
                nums[top++] = x2 + x1;
                break;
            case '-':
                nums[top++] = x2 - x1;
                break;
            case '*':
                nums[top++] = x2 * x1;
                break;
            case '/':
                nums[top++] = x2 / x1;
                break;
            case '^':
                nums[top++] = pow(x2, x1);
                break;
            default:
                printf("[ERROR] Invalid operator: \"%c\".\n", op);
                return INVALID_OPERATOR;
            }
        }
    }
    Number result = nums[--top];
    return result;
}

Number Calculation::get_value() const
{
    return this->value;
}

Calculation& Calculation::operator=(const Calculation &other)
{
    this->raw = other.raw;
    this->value = other.value;
    return *this;
}

Calculation Calculation::operator+(const Calculation &other)
{
    Calculation res;
    res.value = other.value + this->value;
    res.raw = std::to_string(res.value);
    return res;
}

Calculation Calculation::operator-(const Calculation &other)
{
    Calculation res;
    res.value = other.value + this->value;
    res.raw = std::to_string(res.value);
    return res;
}

Calculation Calculation::operator*(const Calculation &other)
{
    Calculation res;
    res.value = other.value + this->value;
    res.raw = std::to_string(res.value);
    return res;
}

#endif // CALCULATION_EXPRESSION_