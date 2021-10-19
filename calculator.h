#ifndef CALCULATOR
#define CALCULATOR

#include "expression.h"
#include "calculation.h"
#include "variable.h"
#include "polynomial.h"
#include "function.h"
#include "matrix.h"
#include "vector.h"

const int MAX_STORAGE_HISTORY_NUMBER = 10;

class Calculator
{
public:
    Calculator() : mode(BASIC_MODE) {};
    ~Calculator() {}

    void run();

    status set_mode();

private:
    Mode mode;

    Expression history[MAX_STORAGE_HISTORY_NUMBER];
};

status Calculator::set_mode()
{
    printf("[INFO] Please enter a number to select a mode:\n");
    printf("[1]: Basic Mode\n");
    printf("[2]: Variable Mode\n");
    printf("[3]: Polynomial Mode\n");
    printf("[4]: Vector Mode\n");
    int mode;
    scanf("%d", &mode);
    getchar();
    switch (mode)
    {
    case 1:
        this->mode = BASIC_MODE;
        printf("[INFO] Switch to the basic mode.\n");
        break;
    case 2:
        this->mode = VARIABLE_MODE;
        printf("[INFO] Switch to the variable mode.\n");
        break;
    case 3:
        this->mode = POLY_MODE;
        printf("[INFO] Switch to the polynomial mode.\n");
        break;
    case 4:
        this->mode = VECTOR_MODE;
        printf("[INFO] Switch to the vector mode.\n");
        break;
    default:
        printf("[ERROR] Please select a valid mode.\n");
        return INVALID_MODE;
    }
    return SUCCESS;
}

void Calculator::run()
{
    printf("HELLO WORLD!\n");

    status s;

    do
    {
        s = set_mode();
        if (s) exit(s);

        printf("[RESULT] The result of the expression is: ");

        getchar();
        printf("[INFO] Enter 'q' to quit.\n");

    } while (getchar() != 'q');
    
    printf("BYE!\n");
    exit(SUCCESS);
}


#endif // CALCULATOR