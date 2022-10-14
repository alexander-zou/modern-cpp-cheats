
/**
 * 
 * @File   : default_member_initializer.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-14 17:58    (+0800)   
 * @Brief  :  
 * 
**/

#if __cplusplus < 201100
#  error "C++11 or better is required"
#endif

#include <iostream>
using namespace std;

class Foo {
    static int _count; // number of instance created.
    // use default member initializer to increase count & assign id:
    int _id = _count ++;

public:
    // use const reference to provide read-only data getter:
    int const &id = _id;
    static int const &count;
};

int Foo::_count = 0;
int const &Foo::count = Foo::_count;

int main() {
    Foo foo1, foo2;
    cout << "foo1.id = " << foo1.id << endl;
    cout << "foo2.id = " << foo2.id << endl;
    cout << "Foo::count = " << Foo::count << endl;
    cout << "Foo().count = " << Foo().count << endl;
    return 0;
}

/*  End of 'default_member_initializer.cpp' */

