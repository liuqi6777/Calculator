#ifndef VECTOR_EXPRESSION_
#define VECTOR_EXPRESSION_

#include "expression.h"
#include <assert.h>

class Vector
{
public:
    Vector(size_t n);
    Vector(const Vector &other);
    ~Vector();

    status input();
    status from_str(string raw);

    Vector& operator=(const Vector &other);
    Vector& operator+(const Vector &other);
    Vector& operator-(const Vector &other);
    Number operator*(const Vector &other);

    friend std::istream& operator>>(std::istream &in, Vector &obj);

private:
    Number *data;
    size_t size;
};

Vector::Vector(size_t n)
{
    this->data = new Number[n];
    this->size = n;
    for (size_t i = 0; i < n; i ++)
    {
        data[i] = 0;
    }
}

Vector::Vector(const Vector &other)
{
    (*this) = other;
}

Vector::~Vector()
{
    if (data != NULL)
    {
        delete[] data;
        data = NULL;
    }
}

status Vector::input()
{
    string raw;
    std::getline(std::cin, raw);
    return from_str(raw);
}

status Vector::from_str(string raw)
{
    size_t p = 0, pos = 0;
    int size_ = 0;
    double num = 0;

    assert(raw[0] == '[');
    raw = raw.substr(1);

    while (raw.length() > 0)
    {
        if (std::isspace(raw[0]))
        {
            raw = raw.substr(1);
        }
        else if (ISDIGIT(raw[0]) || raw[0] == '-') // number
        {
            num = std::stod(raw, &pos);
            data[p++] = num;
            raw = raw.substr(pos);
        }
        else if (raw[0] == ',')
        {
            size_ ++;
            raw = raw.substr(1);
        }
        else if (raw[0] == ']')
        {
            size_ ++;
            break;
        }
        else
        {
            printf("[ERROR] Invalid input.\n");
            return INVALID_INPUT;
        }
    }
    return SUCCESS;
}

Vector& Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        size = other.size;
        data = new Number[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }
    return *this;
}

Vector& Vector::operator+(const Vector &other)
{
    if (this->size != other.size)
    {
        printf("[ERROR] The dimesions of two vectors are NOT equal.\n");
        return *this;
    }
    for (size_t i = 0; i < size; i ++)
    {
        this->data[i] += other.data[i];
    }
    return *this;
}

Vector& Vector::operator-(const Vector &other)
{
    if (this->size != other.size)
    {
        printf("[ERROR] The dimesions of two vectors are NOT equal.\n");
        return *this;
    }
    for (size_t i = 0; i < size; i ++)
    {
        this->data[i] -= other.data[i];
    }
    return *this;
}

Number Vector::operator*(const Vector &other)
{
    if (this->size != other.size)
    {
        printf("[ERROR] The dimesions of two vectors are NOT equal.\n");
        return 0;
    }
    Number ret = 0;
    for (size_t i = 0; i < size; i ++)
    {
        ret += this->data[i] * other.data[i];
    }
    return ret;
}

#endif // VECTOR_EXPRESSION_