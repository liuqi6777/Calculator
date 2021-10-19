#ifndef POLYNOMIAL_EXPRESSION_
#define POLYNOMIAL_EXPRESSION_

#include"expression.h"

typedef struct PolyItem PolyItem;
typedef PolyItem* PolyNode;

struct PolyItem
{
    Number c;
    int power;
    PolyNode next;
};

class Polynomial : public Expression
{
public:
    Polynomial();
    Polynomial(const string &raw);
    Polynomial(const Polynomial &other);
    ~Polynomial();

    status input();
    status output();
    status parse();

    status insert(PolyNode p);
    status set_null();
    status sort();

    Polynomial& operator=(const Polynomial &other);
    Polynomial& operator+(const Polynomial &other);
    Polynomial& operator-(const Polynomial &other);
    Polynomial& operator*(const Polynomial &other);

    Polynomial& diff(int y);

    friend std::ostream &operator<<(std::ostream &out, const Polynomial &obj);
    friend std::istream &operator>>(std::istream &in, const Polynomial &obj);

private:
    string raw;
    PolyNode head;
};

Polynomial::Polynomial()
{
    head = new PolyItem;
    head->c = 0;
    head->power = 0;
    head->next = 0x0;
}

Polynomial::Polynomial(const string &raw)
{
    head = new PolyItem;
    head->c = 0;
    head->power = 0;
    head->next = 0x0;
    this->raw = raw;
    this->parse();
}

Polynomial::Polynomial(const Polynomial &other)
{
    head = new PolyItem;
    head->c = 0;
    head->power = 0;
    head->next = 0x0;
    this->raw = other.raw;
    *this = other;
}

Polynomial::~Polynomial()
{
    set_null();
}

status Polynomial::input()
{   
    std::cout << "[INFO] Please input the polynomial:" << std::endl;
    getline(std::cin, raw);
    return SUCCESS;
}

status Polynomial::output()
{
    std::cout << this->raw << std::endl;
    return SUCCESS;
}

status Polynomial::parse()
{
    string str(raw);
    Number num;
    size_t pos;
    while (str.length() > 0)
    {
        PolyNode pn = new PolyItem;
        if (ISDIGIT(str[0]) || (ISDIGIT(str[1]) && (str[0] == '-' || str[0] == '+'))) // get a number
        {
            num = stod(str, &pos);
            pn->c = num;
            str = str.substr(pos);
            if (str.length() == 0)
            {
                pn->power = 0;
                this->insert(pn);
                break;
            }
            assert(str[0] == '*');
            str = str.substr(1);;
            assert(str[0] == 'x');
        }
        else if (str[0] == '-' || str[0] == '+')
        {
            pn->c = str[0] == '-' ? -1 : 1;
            str = str.substr(1);;
            assert(str[0] == 'x');
        }
        else if (str[0] == 'x')
            pn->c = 1;
        else
            break;
        str = str.substr(1);;
        if (str[0] == '^')
        {
            str = str.substr(1);;
            num = stod(str, &pos);
            pn->power = num;
            str = str.substr(pos);
        }
        else
            pn->power = 1;
        this->insert(pn);
    }
    this->sort();
    return SUCCESS;
}

status Polynomial::insert(PolyNode p)
{
    p->next = this->head->next;
    this->head->next = p;
    return SUCCESS;
}

status Polynomial::set_null()
{
    if (head->next != NULL)
    {
        PolyNode p, tmp;
        p = head->next;
        delete head;

        while (p != NULL)
        {
            tmp = p->next;
            delete p;
            p = tmp;
        }
    }
    return SUCCESS;
}

status Polynomial::sort()
{
    PolyNode pre, p, tail;
    tail = NULL;
    while (head->next != tail)
    {
        pre = head;
        p = head->next;
        while (p->next != tail)
        {
            if (p->power < p->next->power)
            {
                pre->next = p->next;
                p->next = pre->next->next;
                pre->next->next = p;
            }
            else
                p = p->next;

            pre = pre->next;
        }
        tail = p;
    }
    return SUCCESS;
}

Polynomial& Polynomial::operator=(const Polynomial &other)
{
    this->head = new PolyItem;
    this->head->next = 0x0;
    PolyNode tmp, p;
    p = this->head;
    tmp = other.head;
    p->c = tmp->c;
    p->power = tmp->power;
    while(tmp->next != NULL)
    {
        p->next = new PolyItem;
        p = p->next;
        tmp = tmp->next;
        p->c = tmp->c;
        p->power = tmp->power;
        p->next = tmp->next;
    }
    return *this;
}

Polynomial& Polynomial::operator+(const Polynomial &other)
{
    PolyNode p1 = this->head->next;
    PolyNode p2 = other.head->next;
    PolyNode pre = this->head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->power == p2->power)
        {
            p1->c += p2->c;
            if (p1->c == 0)
            {
                PolyNode tmp = p1;
                p1 = p1->next;
                pre->next = p1;
                p2 = p2->next;
                delete tmp;
            }
            else
            {
                p1 = p1->next;
                p2 = p2->next;
                pre = pre->next;
            }
        }
        else if (p1->power > p2->power)
        {
            while (p1->next != NULL && p1->next->power > p2->power)
            {
                p1 = p1->next;
                pre = pre->next;
            }
            if (p1->next && p1->next->power == p2->power)
            {
                p1 = p1->next;
                pre = pre->next;
                continue;
            }
            PolyNode tmp = new PolyItem;
            tmp->c = p2->c;
            tmp->power = p2->power;

            tmp->next = p1->next;
            p1->next = tmp;
            pre = tmp;
            p1 = tmp->next;
            p2 = p2->next;
        }
        else if (p1->power < p2->power)
        {
            PolyNode tmp = new PolyItem;
            tmp->c = p2->c;
            tmp->power = p2->power;

            tmp->next = p1;
            pre->next = tmp;
            p2 = p2->next;
            pre = pre->next;
        }
    }
    while (p2 != NULL)
    {
        PolyNode tmp = new PolyItem;
        tmp->c = p2->c;
        tmp->power = p2->power;
        p1->next = tmp;
        p1 = p1->next;
        p2 = p2->next;
    }
    return *this;
}

Polynomial& Polynomial::operator-(const Polynomial &other)
{
    PolyNode p1 = this->head->next;
    PolyNode p2 = other.head->next;
    PolyNode pre = this->head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->power == p2->power)
        {
            p1->c -= p2->c;
            if (p1->c == 0)
            {
                PolyNode tmp = p1;
                p1 = p1->next;
                pre->next = p1;
                p2 = p2->next;
                delete tmp;
            }
            else
            {
                p1 = p1->next;
                p2 = p2->next;
                pre = pre->next;
            }
        }
        else if (p1->power > p2->power)
        {
            while (p1->next != NULL && p1->next->power > p2->power)
            {
                p1 = p1->next;
                pre = pre->next;
            }
            if (p1->next && p1->next->power == p2->power)
            {
                p1 = p1->next;
                pre = pre->next;
                continue;
            }
            PolyNode tmp = new PolyItem;
            tmp->c = -p2->c;
            tmp->power = p2->power;

            tmp->next = p1->next;
            p1->next = tmp;
            pre = tmp;
            p1 = tmp->next;
            p2 = p2->next;
        }
        else if (p1->power < p2->power)
        {
            PolyNode tmp = new PolyItem;
            tmp->c = -p2->c;
            tmp->power = p2->power;

            tmp->next = p1;
            pre->next = tmp;
            p2 = p2->next;
            pre = pre->next;
        }
    }
    while (p2 != NULL)
    {
        PolyNode tmp = new PolyItem;
        tmp->c = -p2->c;
        tmp->power = p2->power;
        p1->next = tmp;
        p1 = p1->next;
        p2 = p2->next;
    }
    return *this;
}

Polynomial& Polynomial::operator*(const Polynomial &other)
{
    PolyNode p1;
    PolyNode p2 = other.head->next;
    Polynomial original(*this);
    *this = *this - original;
    while (p2 != NULL)
    {
        Polynomial tmp(original);
        p1 = tmp.head->next;
        while (p1 != NULL)
        {
            p1->c *= p2->c;
            p1->power += p2->power;
            p1 = p1->next;
        }
        // std::cout << "[DEBUG] Temp:  " << tmp << std::endl;
        *this = *this + tmp;
        // std::cout << "[DEBIG] Step:  " << *this << std::endl;
        p2 = p2->next;
    }
    return *this;
}

Polynomial& Polynomial::diff(int y)
{
    assert(y >= 0);
    PolyNode p;
    p = this->head->next;
    while (y > 0)
    {
        while (p != NULL)
        {
            if (p->power)
            {
                p->c *= p->power;
                p->power -= 1;
            }
            else
            {
                p->c = 0;
            }
            p = p->next;
        }
        y --;
    }
    return *this;
}

#endif // POLYNOMIAL_EXPRESSION_