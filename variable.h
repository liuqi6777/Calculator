#ifndef VARIABLE_EXPRESSION_
#define VARIABLE_EXPRESSION_

#include"expression.h"
#include"calculation.h"

class VariableExpression : public Calculation
{
public:
    VariableExpression();
    VariableExpression(const string &raw);
    VariableExpression(const VariableExpression &other);
    ~VariableExpression();

    status input();
    status output();
    status parse();

    status set_var_name(string name);
    status set_var_value(Number value);
    Number get_var_value();
    Number get_value() const;

    VariableExpression& operator=(const VariableExpression &other);

    status replace(string &str, string _old, string _new="");

    friend std::ostream& operator<<(std::ostream &out, VariableExpression &obj);
    friend std::istream& operator>>(std::istream &in, VariableExpression &obj);

private:
    string raw;
    string var_name;
    Number var_value;
    Number value;
};

VariableExpression::VariableExpression()
{

}

VariableExpression::VariableExpression(const std::string &raw)
{
    this->raw = raw;
}

VariableExpression::VariableExpression(const VariableExpression &other)
{
    this->raw = other.raw;
    this->value = other.value;
    this->var_name = other.var_name;
    this->var_value = other.var_value;
}

VariableExpression::~VariableExpression()
{

}

status VariableExpression::input()
{   
    std::cout << "[INFO] Please input the expression:" << std::endl;
    getline(std::cin, raw);
    return SUCCESS;
}

status VariableExpression::output()
{
    std::cout << "[RESULT] The rusult is : " << this->value << "." << std::endl;
    return SUCCESS;
}

status VariableExpression::parse()
{
    string str(this->raw);
    replace(str, this->var_name, std::to_string(this->var_value));
    this->value = Calculation::parse(str);
    return SUCCESS;
}

status VariableExpression::set_var_name(string name)
{
    this->var_name = name;
    return SUCCESS;
}

status VariableExpression::set_var_value(Number value)
{
    this->var_value = value;
    this->parse();
    return SUCCESS;
}

Number VariableExpression::get_var_value()
{
    return this->var_value;
}

Number VariableExpression::get_value() const
{
    return this->value;
}

status VariableExpression::replace(string &str, string old, string _new)
{
    size_t pos;
    while((pos = str.find(old)) != string::npos)
    {
        str.replace(pos, old.length(), _new);
    }
    return SUCCESS;
}

VariableExpression& VariableExpression::operator=(const VariableExpression &other)
{
    this->raw = other.raw;
    this->value = other.value;
    this->var_name = other.var_name;
    this->var_value = other.var_value;
    return *this;
}

#endif // VARIABLE_EXPRESSION_