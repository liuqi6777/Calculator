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
    Function funcs[MAX_STORAGE_HISTORY_NUMBER];
    size_t funcs_count = 0;
};

status Calculator::set_mode()
{
    printf("[INFO] Please enter a number to select a mode:\n");
    printf("[1]: Basic Mode\n");
    printf("[2]: Variable Mode\n");
    printf("[3]: Polynomial Mode\n");
    printf("[4]: Vector Mode\n");
    printf("[5]: Matrix Mode\n");
    printf("[6]: Function Mode\n");
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
    case 5:
        this->mode = MATRIX_MODE;
        printf("[INFO] Switch to the matrix mode.\n");
        break;
    case 6:
        this->mode = FUNCTION_MODE;
        printf("[INFO] Switch to the function mode.\n");
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

        if (mode == BASIC_MODE)
        {
            Calculation e;
            e.input();
            e.parse();
            e.output();
        }

        else if (mode == VARIABLE_MODE)
        {
            VariableExpression e;
            printf("[INFO] Please input the variable's name.\n");
            string name;
            std::getline(std::cin, name);
            e.input();
            e.set_var_name(name);
            Number n;
            do
            {
                printf("[INFO] Please input the value of x.\n");
                scanf("%lf", &n);
                getchar();
                e.set_var_value(n);
                e.output();
                printf("[INFO] Enter 'q' to quit Variable Mode.\n");
            } while (getchar() != 'q');
        }

        else if (mode == POLY_MODE)
        {

        }

        else if (mode == VECTOR_MODE)
        {

        }
            
        else if (mode == MATRIX_MODE)
        {

        }

        else if (mode == FUNCTION_MODE)
        {
            do
            {
                printf("[INFO] Please DEFINE or RUN a function.\n");
                string str;
                getline(std::cin, str);

                if (str.substr(0, 3) == "DEF")
                {
                    int pos = str.find_first_of('=');

                    string var_name(1, str[str.find_first_of('(') + 1]);
                    string func_name(1, str[str.find_first_of('(') - 1]);
                    str = str.substr(pos+1);
                    
                    string func_in = "("; func_in += var_name; func_in += ')'; 
                    while ((pos = str.find(func_in)) != string::npos)
                    {
                        string func_in_name(1, str[pos-1]);
                        for (int i = 0; i < funcs_count; i++)
                        {
                            if (func_in_name == funcs[i].get_func_name())
                            {
                                string expr;
                                expr.push_back('(');
                                expr += funcs[i].get_func();
                                expr.push_back(')');
                                str.replace(pos-1, 4, expr);
                                if (funcs[i].get_var_name() != var_name)
                                    while((pos = str.find(funcs[i].get_var_name())) != string::npos)
                                        str.replace(pos, 1, var_name);
                                break;
                            }
                        }
                    }
                    
                    Function f(str);
                    f.set_var_name(var_name);
                    f.set_func_name(func_name);

                    funcs[funcs_count ++] = f;
                }
                else if (str.substr(0, 3) == "RUN")
                {
                    string func_name(1, str[str.find_first_of('(') - 1]);
                    for (int i = 0; i < funcs_count; i ++)
                    {
                        if (func_name == funcs[i].get_func_name())
                        {
                            Function f(funcs[i]);
                            f.parse_var_value(str);
                            double res = f.get_value();
                            printf("[RESULT] The result is %lf.\n", res);
                            break;
                        }
                    }
                }
                else
                {
                    printf("[ERROR] Invalid operation.\n");
                }
                printf("[INFO] Enter 'q' to quit Function Mode.\n");
            } while(getchar() != 'q');

        }
        
        printf("[INFO] Enter 'q' to quit.\n");

    } while (getchar() != 'q');
    
    printf("BYE!\n");
    exit(SUCCESS);
}


#endif // CALCULATOR