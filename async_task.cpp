
/**
 * 
 * @File   : async_task.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-13 14:54    (+0800)   
 * @Brief  :  
 * 
**/

#include <future>

#include <thread> // sleep_for()
#include <chrono> // duration
#include <cstdio> // printf()


#if __cplusplus < 201100
#  error "C++11 or better is required"
#endif

char const *indent( int n) {
    constexpr static char SPACES[] =
        "                                                           "
        "                                                           "
        "                                                           "
        "                                                           ";
    return SPACES + sizeof( SPACES)-1 - 5*n;
}

int foobar( int a, int b) {
    printf( "%s/`Task %d+%d started.\n", indent( a), a, b);

#if __cplusplus < 201400
    std::this_thread::sleep_for( std::chrono::milliseconds( 200));
#else // for c++14 or later:
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 200ms);
#endif

    printf( "%s\\_Task %d+%d finished.\n", indent(a), a, b);
    return a+b;
}

struct Foo {
    int bar( int a, int b) {
        return foobar( a, b);
    }
};

int main() {
    // Async Mode:

    auto f = std::async( std::launch::async,
                            foobar, 2, 8);  // Task 2
    foobar( 1, 9);                          // Task 1
    f.get();                                // Wait for Task 2

    // Async Mode ( with Object Method ):

    Foo foo;
    f = std::async( std::launch::async,
                        &Foo::bar, foo, 4, 6);  // Task 4
    foobar( 3, 7);                      // Task 3
    f.get();                            // Wait for Task 4

    // Defer Mode:

    f = std::async( std::launch::deferred, foobar, 5, 5);   // Task 5
    foobar( 6, 4);                                          // Task 6
    printf( "final result is %d.\n", f.get());               // Do Task 5

    return 0;
}


/*  End of 'async_task.cpp' */

