#include <iostream>
#include "calculator.h"
#include "calculator.cpp"

void test();

int main() {
    std::cout << "Hello, world!\n";
    Calculator app;
    app.run();
    // test();
    return 0;
}

void test()
{
    Poly poly1('x');
    PolyItem p1 = {3.6, 0};
    PolyItem p2 = {-2, 1};
    PolyItem p3 = {4, 3};
    PolyNode ptr1 = new PolyItem;
    ptr1 = &p1;
    PolyNode ptr2 = new PolyItem;
    ptr2 = &p2;
    PolyNode ptr3 = new PolyItem;
    ptr3 = &p3;
    poly1.insert(ptr3);
    poly1.insert(ptr1);
    poly1.insert(ptr2);
    poly1.__sort_descending();
    std::cout << poly1 << std::endl;

    Poly poly2('x');
    PolyItem p4 = {4, 2, NULL};
    PolyItem p5 = {-2, 3, NULL};
    PolyItem p6 = {1, 6, NULL};
    PolyNode ptr4 = new PolyItem;
    ptr4 = &p4;
    PolyNode ptr5 = new PolyItem;
    ptr5 = &p5;
    PolyNode ptr6 = new PolyItem;
    ptr6 = &p6;
    poly2.insert(ptr4);
    poly2.insert(ptr5);
    poly2.insert(ptr6);
    poly2.__sort_descending();
    std::cout << poly2 << std::endl;

    // Poly poly3;
    // poly3 = poly1 + poly2;
    // std::cout << poly3 << std::endl;

    Poly poly4;
    poly4 = poly1 * poly2;
    std::cout << poly4 << std::endl;
}
