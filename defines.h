#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#ifndef NUMBER_TYPE
#define NUMBER_TYPE
typedef double Number;
#endif

typedef enum
{
    SUCCESS,
    ERROE,
    OVERFLOW,
    INVALID_INPUT,
    INVALID_OPERATOR,
    INVALID_MODE,
    ILLEGAL_OPERATION,
    TYPE_ERROR,
    OUT_OF_RANGE
} status;

typedef enum
{
    OPERATOR,
    NUMBER,
    VARIABLE,
    POLY,
    VECTOR,
} itemType;

typedef enum
{
    BASIC_MODE = 1,
    VARIABLE_MODE,
    POLY_MODE,
    VECTOR_MODE
} Mode;

typedef char operators;

const operators OPS[] = {
    '#',
    '+',
    '-',
    '*',
    '/',
    '(',
    ')',
};

#endif // GLOBAL_DEFINES_H