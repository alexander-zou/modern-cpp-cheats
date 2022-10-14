
/**
 * 
 * @File   : class_aggregate_init.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-14 17:17    (+0800)   
 * @Brief  :  
 * 
**/

// see https://en.cppreference.com/w/cpp/language/aggregate_initialization for more.

#include <iostream>
#include <string>

using namespace std;

struct Foo {
    int x;
    float y;
    string s;
    void print() const {
        cout << "  x:" << x;
        cout << "  y:" << y;
        cout << "  s:" << s << endl;
    }
};

void ordinary_init() {
#if __cplusplus >= 201100
    Foo foo1{ 12, 34.56, "789"};
    foo1.print();

    Foo foo2{ 12};  // y & s are not initialized! Compiler should show warning.
    foo2.print();

    Foo foo3{};     // Legitimate! All fields will be zero-initialized.
    foo3.print();
#endif
}

void designated_init() {
#if __cplusplus >= 202000
    Foo{ .x=654, .y{32.1}, .s="0"}.print();

    // work with default-member-initializer:
    struct Bar {
        int x = 1;
        float y = 2;
        string s = "3";
        void print() const {
            cout << "  x:" << x;
            cout << "  y:" << y;
            cout << "  s:" << s << endl;
        }
    };
    Bar{ .y=9999}.print();
#endif
}

int main() {
    ordinary_init();
    designated_init();
    return 0;
}


/*  End of 'class_aggregate_init.cpp' */

