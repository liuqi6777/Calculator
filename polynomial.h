#ifndef POLYNOMIAL
#define POLYNOMIAL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<iostream>

#include "defines.h"


typedef struct PolyItem PolyItem;
typedef PolyItem* PolyNode;
typedef PolyItem* Polynomial;

struct PolyItem {
    Number c;
    int power;
    PolyNode next;
};


class Poly
{
public:
    Poly ();
    Poly(char var);
    Poly(const Poly & rhs); // 深拷贝
    ~Poly();

    status set();
    status insert(PolyNode item);
    status set_null();

    status add();
    status sub();
    status mul();

    Poly& operator + (const Poly & rhs);
    Poly& operator - (const Poly & rhs);
    Poly& operator * (const Poly & rhs);

    friend std::ostream& operator << (std::ostream& out, Poly &p);
    
    Poly diff(int y);
    status __sort_descending();

private:

    inline bool __cmp(const PolyNode &p1, const PolyNode &p2) {return p1->power < p2->power; }

    Polynomial head;
    char var;
};

Poly::Poly()
{
    head = new PolyItem;
    head->next = nullptr;
    this->var = 'x';
}

Poly::Poly(char var)
{
    
    head = new PolyItem;
    head->next = NULL;
    this->var = var;
}

Poly::Poly(const Poly &rhs)
{
    this->var = rhs.var;
    head = new PolyItem;
    PolyNode tmp, p;
    p = this->head;
    tmp = rhs.head;
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
}

Poly::~Poly()
{
    set_null();
}

status Poly::set()
{
    // TODO
    return SUCCESS;
}

status Poly::insert(PolyNode item)
{
    item->next = this->head->next;
    this->head->next = item;

    return SUCCESS;
}

status Poly::set_null()
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

Poly& Poly::operator + (const Poly & rhs)
{
    // inplace
    PolyNode p1 = this->head->next;
    PolyNode p2 = rhs.head->next;
    PolyNode pre = this->head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->power == p2->power)
        {
            p1->c += p2->c;
            if (0 && p1->c == 0)
            {
                PolyNode tmp = p1;
                p1 = p1->next;
                pre->next = p1;
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

Poly& Poly::operator - (const Poly & rhs)
{
    PolyNode p1 = this->head->next;
    PolyNode p2 = rhs.head->next;
    PolyNode pre = this->head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->power == p2->power)
        {
            p1->c -= p2->c;
            if (0 && p1->c == 0)
            {
                PolyNode tmp = p1;
                p1 = p1->next;
                pre->next = p1;
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

Poly& Poly::operator * (const Poly & rhs)
{
    PolyNode p1;
    PolyNode p2 = rhs.head->next;
    Poly original(*this);
    *this = *this - original;
    while (p2 != NULL)
    {
        Poly tmp(original);
        p1 = tmp.head->next;
        while (p1 != NULL)
        {
            p1->c *= p2->c;
            p1->power += p2->power;
            p1 = p1->next;
        }
        std::cout << "Temp:  " << tmp << std::endl;
        *this = *this + tmp;
        std::cout << "Step:  " << *this << std::endl;
        p2 = p2->next;
    }
    return *this;
}

std::ostream& operator << (std::ostream& out, Poly &p)
{
    out << "Poly<";
    PolyNode tmp;
    tmp = p.head->next;
    char var = 'x'; // TODO

    out << tmp->c << "*" << var << "^" << tmp->power;
    tmp = tmp->next;

    while (tmp != NULL)
    {
        if (tmp->c != 0)
        {
            if (tmp->c > 0)
                out << '+';
            out << tmp->c;
            if (tmp->power)
                out << "*" << var << "^" << tmp->power;
        }
        tmp = tmp->next;
    }

    out << ">";
    return out;
}

status Poly::__sort_descending()
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


#endif // POLYNOMIAL