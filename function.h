#ifndef FUNCTION_EXPRESSION_
#define FUNCTION_EXPRESSION_

#include"expression.h"
#include"calculation.h"

class Function : public Calculation
{
public:
    Function();
    Function(const string &raw);
    Function(const Function &other);
    ~Function();

    status input();
    status output();
    status parse();

    status set_var_name(string name);
    status set_var_value(Number value);
    status parse_var_value(string expr);
    Number get_var_value();
    Number get_value() const;

    status set_func_name(string name) {this->func_name = name; return SUCCESS;}
    string get_func_name() {return this->func_name;}
    string get_func() {return this->raw;}
    string get_var_name() {return this->var_name;}

    status replace(string &str, string _old, string _new="");

    Function& operator=(const Function &other);

    friend std::ostream& operator<<(std::ostream &out, Function &obj);
    friend std::istream& operator>>(std::istream &in, Function &obj);

private:
    string raw;
    string var_name;
    string func_name;
    Number var_value;
    Number value;
};

Function::Function()
{

}

Function::Function(const std::string &raw)
{
    this->raw = raw;
}

Function::Function(const Function &other)
{
    this->raw = other.raw;
    this->value = other.value;
    this->func_name = other.func_name;
    this->var_name = other.var_name;
}

Function::~Function()
{

}

status Function::input()
{   
    std::cout << "[INFO] Please input the function:" << std::endl;
    getline(std::cin, raw);
    return SUCCESS;
}

status Function::output()
{
    std::cout << "[RESULT] The rusult of " << this->func_name << "(" << this->var_value << ")" << "is : " << this->value << "." << std::endl;
    return SUCCESS;
}

status Function::parse()
{
    string str(this->raw);
    replace(str, this->var_name, std::to_string(this->var_value));
    this->value = Calculation::parse(str);
    return SUCCESS;
}

status Function::set_var_name(string name)
{
    this->var_name = name;
    return SUCCESS;
}

status Function::set_var_value(Number value)
{
    this->var_value = value;
    this->parse();
    return SUCCESS;
}

status Function::parse_var_value(string expr)
{
    string tmp;
    size_t start = 0, end = 0;
    start = expr.find('(');
    end = expr.find(')');
    tmp = expr.substr(start+1, end);
    this->var_value = std::stod(tmp);

    string str = this->raw;
    replace(str, this->var_name, std::to_string(this->var_value));
    this->value = Calculation::parse(str);

    return SUCCESS;
}

Number Function::get_var_value()
{
    return this->var_value;
}

Number Function::get_value() const
{
    return this->value;
}

status Function::replace(string &str, string old, string _new)
{
    size_t pos;
    while((pos = str.find(old)) != string::npos)
    {
        str.replace(pos, old.length(), _new);
    }
    return SUCCESS;
}

Function& Function::operator=(const Function &other)
{
    this->raw = other.raw;
    this->value = other.value;
    this->var_name = other.var_name;
    this->var_value = other.var_value;
    this->func_name = other.func_name;
    return *this;
}

#endif // FUNCTION_EXPRESSION_