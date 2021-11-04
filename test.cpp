#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do \
    { \
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_EQ_CSTRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength + 1) == 0, expect, actual, "%s")
#define EXPECT_EQ_STRING(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%s")


#define TEST_CALCULATION(expect, expression)\
    do {\
        Calculation c(expression);\
        EXPECT_EQ_INT(SUCCESS, c.parse()); \
        EXPECT_EQ_DOUBLE(expect, c.get_value());\
    } while (0)

static void test_calculation()
{
    TEST_CALCULATION(0, "0");
    TEST_CALCULATION(3.33, "3.33");
    TEST_CALCULATION(1, "-3+4*2-2^2");
    TEST_CALCULATION(9, "2*4+1");
    TEST_CALCULATION(2, "3+(10-(4*2))*7-3*5");
    TEST_CALCULATION(1.5, "2.25/1.5");
    TEST_CALCULATION(1, "0.99999+0.000001*10");
}

#define TEST_VARIABLE_EXPRESSION(expect, expression, name, value) \
    do {\
        VariableExpression v(expression); \
        EXPECT_EQ_INT(SUCCESS, v.set_var_name(name)); \
        EXPECT_EQ_INT(SUCCESS, v.set_var_value(value)); \
        EXPECT_EQ_INT(SUCCESS, v.parse()); \
        EXPECT_EQ_DOUBLE(expect, v.get_value()); \
    } while (0)

static void test_variable_expression()
{
    TEST_VARIABLE_EXPRESSION(15, "3*(x+4)-2*x", "x", 3);
}

#define TEST_POLYNOMIAL_OPER(expect, expression_1, expression_2, operator) \
    do { \
        Polynomial p1(expression_1); \
        Polynomial p2(expression_2); \
        switch (operator) \
        { \
        case '+': p1 + p2; break; \
        case '-': p1 - p2; break; \
        case '*': p1 * p2; break; \
        } \
        EXPECT_EQ_STRING(expect, (string)p1); \
    } while (0)

#define TEST_POLYNOMIAL_DIFF(expect, expression, num) \
    do { \
        Polynomial p(expression); \
        p.diff(num); \
        EXPECT_EQ_STRING(expect, (string)p); \
    } while (0)

static void test_polynomial()
{
    TEST_POLYNOMIAL_OPER("3.000000*x^2+2.000000*x^1", "3*x^2", "2*x^1", '+');
    TEST_POLYNOMIAL_DIFF("6.000000*x^1+2.000000", "3*x^2+2*x^1", 1);
}

#define TEST_FUNCTION(expect, expression, value) \
    do { \
        Function f(expression); \
        EXPECT_EQ_INT(SUCCESS, f.set_var_name("x")); \
        EXPECT_EQ_INT(SUCCESS, f.parse_var_value(value)); \
        EXPECT_EQ_DOUBLE(expect, f.get_value()); \
    } while(0)

static void test_function()
{
    // TEST_FUNCTION(7, "f(x)=x*2+1", "f(3)");
}

static void test_matrix()
{

}

static void test_access()
{
    test_calculation();
    test_variable_expression();
    test_polynomial();
    test_function();
    test_matrix();
}

int main(int argc, char *argv[])
{
    //  ctest --verbose 
    test_access();
    printf("[TEST] %d/%d (%3.2f%%) passed.\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}