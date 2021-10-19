#ifndef EXPRESSION_
#define EXPRESSION_

#include<iostream>
#include<string>
#include<cmath>
#include<assert.h>
#include"defines.h"

using std::string;

class Expression
{
public:
    Expression() {}
    Expression(const Expression& other) {};
    ~Expression() {}

    virtual status input() { return SUCCESS; };
    virtual status output() { return SUCCESS; };
    virtual status parse() { return SUCCESS; };

    // virtual Expression& operator=(Expression &other);
    
    // virtual Expression& add(Expression &other);
    // virtual Expression& sub(Expression &other);
    // virtual Expression& mul(Expression &other);
};

#endif // EXPRESSION_