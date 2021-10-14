#ifndef VECTOR_
#define VECTOR_

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<iostream>

#include "defines.h"
#include "array.h"

const int INIT_SIZE = 2;

class Vector
{
public:
    Vector();
    Vector(size_t size);
    Vector(const Vector & rhs);
    ~Vector();

    status set(size_t size, Array &src);
    status put(int index, Number value);

    status add();
    status sub();
    status mul();

    Vector& operator + (const Vector & rhs);
    Vector& operator - (const Vector & rhs);
    Number operator * (const Vector & rhs);
    Number operator [] (int index);

    Vector& operator=(const Vector & rhs);

    double norm(); // 向量的模
    double cos(Vector & v);

    size_t get_size();

    friend std::ostream& operator << (std::ostream& out, const Vector& v);

private:
    Number * array;
    size_t size; // 向量维度
};

Vector::Vector()
{
    size = INIT_SIZE;
    this->array = new Number[INIT_SIZE];
}

Vector::Vector(size_t size)
{
    this->size = size;
    this->array = new Number[size];

    for (size_t i = 0; i < size; i ++)
        this->array[i] = 0;
}

Vector::Vector(const Vector & rhs)
{
    this->size = rhs.size;
    if (this->array != NULL)
        delete[] this->array;
    if (rhs.array != NULL)
    {
        this->array = new Number[this->size];
        for (size_t i = 0; i < this->size; i ++)
        {
            this->array[i] = rhs.array[i];
        }
    }
}

Vector::~Vector()
{
    if (this->array != NULL)
        delete[] this->array;
}

status Vector::set(size_t size, Array &src)
{
    assert(src.array != NULL && src.used == size);
    for (size_t i = 0; i < size; i ++)
        this->array[i] = src.array[i];
    return SUCCESS;
}

status Vector::put(int index, Number value)
{
    if (index < 0 || index >= size)
        return OUT_OF_RANGE;
    this->array[index] = value;
    return SUCCESS;
}

Vector& Vector::operator +(const Vector & rhs)
{
    assert(this->array != NULL);
    assert(rhs.array != NULL);
    if (this->size != rhs.size)
    {
        printf("[ERROR]\n");
    }
    assert(this->size == rhs.size);

    for (size_t i = 0; i < size; i ++)
    {
        this->array[i] += rhs.array[i];
    }
    return *this;
}

Vector& Vector::operator -(const Vector & rhs)
{
    assert(this->array != NULL);
    assert(rhs.array != NULL);
    if (this->size != rhs.size)
    {
        printf("[ERROR]\n");
    }
    assert(this->size == rhs.size);

    for (size_t i = 0; i < size; i ++)
    {
        this->array[i] -= rhs.array[i];
    }
    return *this;
}

Number Vector::operator *(const Vector & rhs)
{
    assert(this->array != NULL);
    assert(rhs.array != NULL);
    if (this->size != rhs.size)
    {
        printf("[ERROR]\n");
    }
    assert(this->size == rhs.size);

    Number res;

    for (size_t i = 0; i < size; i ++)
    {
        res += this->array[i] * rhs.array[i];
    }
    return res;
}

Number Vector::operator [](int index)
{
    return this->array[index];
}

Vector& Vector::operator=(const Vector &rhs)
{
    this->size = rhs.size;
    if (this->array != NULL)
        delete[] this->array;
    if (rhs.array != NULL)
    {
        this->array = new Number[this->size];
        for (size_t i = 0; i < this->size; i ++)
        {
            this->array[i] = rhs.array[i];
        }
    }
    return *this;
}

double Vector::norm()
{
    double a = 0;
    for (size_t i = 0; i < size; i ++)
    {
        a += this->array[i] * this->array[i];
    }
    return sqrt(a);
}

double Vector::cos(Vector & rhs)
{
    return (*this) * rhs / (double)((*this).norm() * rhs.norm());
}

size_t Vector::get_size()
{
    return this->size;
}

std::ostream& operator << (std::ostream& out, Vector& v)
{
    out << "Vector<";
    for (size_t i = 0; i < v.get_size(); i ++)
        out << v[i] << ", ";
    out << "size=" << v.get_size() << ">";
    return out;
}

#endif // VECTOR_
