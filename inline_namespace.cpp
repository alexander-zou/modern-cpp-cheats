
/**
 * 
 * @File   : inline_namespace.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-14 16:57    (+0800)   
 * @Brief  :  
 * 
**/

#if __cplusplus < 201100
#  error "C++11 or better is required"
#endif

// Basically, inline-namespace split one big namespace into parts.

namespace OneBigNamespace {

    inline namespace PartA {
        void foo() {}
    }

    inline namespace PartB {
        void bar() {}
    }

    void foobar() {}

} // namespace OneBigNamespace

void using_part_a() {
    using namespace OneBigNamespace::PartA;
    foo();      // OK!
    //bar();    // NOT visiable here!
    //foobar(); // NOT visiable here!
}

void using_whole_namespace() {
    using namespace OneBigNamespace;
    foo();      // OK!
    bar();      // OK!
    foobar();   // OK!
}

int main() {
    return 0;
}

/*  End of 'inline_namespace.cpp' */

