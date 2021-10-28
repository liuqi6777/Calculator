#ifndef VECTOR_EXPRESSION_
#define VECTOR_EXPRESSION_

#include"expression.h"
#include"matrix.h"

class Vector : public Matrix
{
public:
    Vector();
    Vector(const string &raw);
    Vector(const Vector &other);
    ~Vector();

    status input();
    status output();
    status parse();

    Vector& operator=(const Vector &other);
    Vector& operator+(const Vector &other);
    Vector& operator-(const Vector &other);
    Vector& operator*(const Vector &other);

    friend std::ostream& operator<<(std::ostream &out, Vector &obj);
    friend std::istream& operator>>(std::istream &in, Vector &obj);

private:
    string raw;
    Number *data;
    size_t size;
};

#endif // VECTOR_EXPRESSION_