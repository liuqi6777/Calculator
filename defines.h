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
    INVALID_INPUT,
    INVALID_OPERATOR,
    INVALID_MODE,
    ILLEGAL_OPERATION,
    TYPE_ERROR,
    OUT_OF_RANGE
} status;

typedef enum
{
    BASIC_MODE = 1,
    VARIABLE_MODE,
    POLY_MODE,
    VECTOR_MODE,
    MATRIX_MODE,
    FUNCTION_MODE
} Mode;

#define ISDIGIT(x) (x >= '0' && x <= '9')
#define ISOPS(x) ( \
    x == '+' || \
    x == '-' || \
    x == '*' || \
    x == '/' || \
    x == '^' || \
    x == '(' || \
    x == ')' || \
    x == '\'' || \
    x == '#')

#endif // GLOBAL_DEFINES_H