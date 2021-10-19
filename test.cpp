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


#define TEST_CALCULATION(expect, expression)\
    do {\
        Calculation c(expression);\
        EXPECT_EQ_INT(SUCCESS, c.parse()); \
        EXPECT_EQ_DOUBLE(expect, c.get_value());\
    } while (0)

static void test_calculation()
{
    TEST_CALCULATION(0, "0");
    TEST_CALCULATION(5, "-3+4*2");
    TEST_CALCULATION(9, "2*4+1");
    TEST_CALCULATION(2, "3+(10-(4*2))*7-3*5");
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

static void test_access()
{
    test_calculation();
    test_variable_expression();
}

int main(int argc, char *argv[])
{
    //  ctest --verbose 
    test_access();
    printf("[TEST] %d/%d (%3.2f%%) passed.\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}