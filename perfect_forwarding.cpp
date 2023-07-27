
/**
 * Copyright (c) 2023 JIIOV. All Rights Reserved
 * 
 * @File   : perfect_forwarding.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2023-07-27 14:54    (+0800)   
 * @Brief  :  
 * 
**/

#include <iostream>
#include <utility>

#if __cplusplus < 201103
#  error "C++11 or better is required"
#endif

// Consider implementing emplace_back() method of container vector:
template<typename T> struct MyVector {
    void emplace_back( T&& v) { // 'T&&' accept both lvalue & rvalue actual parameter, this is called 'Universal Reference'
        // ...
        // ALWAYS has to call new somewhere:
        T *p = new T( v);
        // ideally, we hope parameter passed into constructor
        // is of the same type as which passed into emplace_back().
        // 这里我们希望传入emplace_back()的参数v的左右引用类型，能够以原样转发
    }
};

// to test type of reference, introduce functions below:

void pseudo_new( int &&v) {
    std::cout << "  Rvalue " << v << " received.\n";
}

void pseudo_new( int &v) {
    std::cout << "  Lvalue " << v << " received.\n";
}

template<typename T>
void pseudo_emplace_back( T &&v) {
    pseudo_new( v);
    // notice v here is a named variable, which makes it a lvalue
    // 注意这里的v是具名变量，因而按标准定义它是左值
    // more info: https://en.cppreference.com/w/cpp/language/value_category

    pseudo_new( std::forward<T>( v));
    // forward() transforms v into rvalue only when v is originally rvalue, so-called 'Perfect Forwarding'
    // forward()仅将原本实参为右值的参数转换为右值，原本为左值的参数保持左值，这就是“完美转发”

    pseudo_new( std::move(v));
    // move() always turns things into rvalues.
}

int main() {
    int x = 123;

    std::cout << "\ncalling with Lvalue x:\n";
    pseudo_emplace_back( x);
    std::cout << "\ncalling with Rvalue move(x):\n";
    pseudo_emplace_back( std::move( x));
    std::cout << "\ncalling with Rvalue 123:\n";
    pseudo_emplace_back( 123);
    return 0;
}


/*  End of 'perfect_forwarding.cpp' */

