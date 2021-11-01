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
    size_t fun_num = 0;
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
            Calculation c;
            c.input();
            c.parse();
            c.output();
        }

        else if (mode == VARIABLE_MODE)
        {

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
                    Function f(str.substr(pos+1));
                    string vn = "";
                    vn += str[str.find_first_of('(') + 1];
                    f.set_var_name(vn);

                    string n = "";
                    n += str[str.find_first_of('(') - 1];
                    // std::cout << n <<  std::endl;
                    f.set_func_name(n);
                    // std::cout << f.get_func_name() << std::endl;

                    funcs[fun_num ++] = f;
                }
                else if (str.substr(0, 3) == "RUN")
                {
                    string func_name = "";
                    func_name += str[str.find_first_of('(') - 1];
                    // std::cout << func_name << std::endl;
                    for (int i = 0; i < fun_num; i ++)
                    {
                        // std::cout << funcs[i].get_func_name() << std::endl;
                        if (func_name == (funcs[i]).get_func_name())
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
                    printf("[ERROR] \n");
                }
                // getchar();
                printf("[INFO] Enter 'q' to quit Function Mode.\n");
            } while(getchar() != 'q');

        }
        
        printf("[INFO] Enter 'q' to quit.\n");

    } while (getchar() != 'q');
    
    printf("BYE!\n");
    exit(SUCCESS);
}


#endif // CALCULATOR