#ifndef EXPRESSION_
#define EXPRESSION_

#include "defines.h"
#include "polynomial.h"
#include "vector.h"

#include<assert.h>


class Data
{
public:
    // TODO: 所有类型统一变成字符串，解析或计算时再进行转换.
    Number num;
    Poly poly;
    Vector vec;
    operators op;

    Data() { };
    ~Data() { };
    Data(const Data &other) 
    { 
        num = other.num; 
        poly = other.poly; 
        vec = other.vec; 
        op = other.op;
    }

    Data &operator=(const Data &other)
    { 
        num = other.num; 
        poly = other.poly; 
        vec = other.vec; 
        op = other.op; 
        return *this;
    }

};

const size_t MAX_LEN = 100;

class ExprItem
{
public:
    Data data;
    itemType type;

    ExprItem() {}
    ExprItem(const ExprItem &rhs);
    ExprItem &operator+(const ExprItem &rhs);
    ExprItem &operator-(const ExprItem &rhs);
    ExprItem &operator*(const ExprItem &rhs);
    ExprItem &operator=(const ExprItem &rhs);

    friend std::ostream &operator<<(std::ostream & out, const ExprItem &e);

};


class Expression
{
public:
    Expression();
    ~Expression();

    ExprItem *expr;
    size_t length;
};

Expression::Expression()
{
    length = MAX_LEN;
    expr = new ExprItem[length];
}

Expression::~Expression()
{
    delete[] expr;
}

ExprItem::ExprItem(const ExprItem &rhs)
{
    type = rhs.type;
    data = rhs.data;
}

ExprItem &ExprItem::operator=(const ExprItem &rhs)
{
    type = rhs.type;
    data = rhs.data;
    return *this;
}

ExprItem &ExprItem::operator+(const ExprItem &rhs)
{
    assert(type == rhs.type);
    switch (type)
    {
    case NUMBER:
        data.num += rhs.data.num;
        break;
    case POLY:
        data.poly = data.poly + rhs.data.poly;
        break;
    case VECTOR:
        data.vec = data.vec + rhs.data.vec;
        break;
    }
    return *this;
}

ExprItem &ExprItem::operator-(const ExprItem &rhs)
{
    assert(type == rhs.type);
    switch (type)
    {
    case NUMBER:
        data.num -= rhs.data.num;
        break;
    case POLY:
        data.poly = data.poly - rhs.data.poly;
        break;
    case VECTOR:
        data.vec = data.vec - rhs.data.vec;
        break;
    }
    return *this;
}

ExprItem &ExprItem::operator*(const ExprItem &rhs)
{
    assert(type == rhs.type);
    switch (type)
    {
    case NUMBER:
        data.num *= rhs.data.num;
        break;
    case VARIABLE:
        // TODO
        break;
    case POLY:
        data.poly = data.poly * rhs.data.poly;
        break;
    case VECTOR:
        // TODO: support vector types
        // data.vec = data.vec * rhs.data.vec;
        break;
    }
    return *this;
}

std::ostream &operator<<(std::ostream & out, ExprItem &e)
{
    switch (e.type)
    {
    case NUMBER:
        out << e.data.num;
        break;
    case VARIABLE:
        // TODO
        break;
    case POLY:
        // TODO
        // std::cout << e.data.poly;
        break;
    case VECTOR:
        out << e.data.vec;
        break;
    }
    return out;
}

#endif // EXPRESSION_
