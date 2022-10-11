
/**
 * 
 * @File   : profile_timer.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-11 10:42    (+0800)   
 * @Brief  :  
 * 
**/

#include <cstdio>
#include <chrono>

#if __cplusplus < 201100

#  error "C++11 or better is required"

#else // if C++11 or later

class Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> _start_time;
public:
    Timer() {
        _start_time = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> past_time = end_time - _start_time;
        printf( "Past Time: %f seconds.\n", past_time.count());
        printf( "Past Time: %lld ms.\n", std::chrono::duration_cast<std::chrono::milliseconds>( past_time).count());
    }
};

int main() {
    constexpr int N = 100000000;

    Timer timer;
    int result = 0;
    int *array = new int[ N];
    for ( int i = 0; i < N; i ++)
        result |= array[ i];
    printf( "result = %d\n", result);

    return 0;
}

#endif // __cplusplus


/*  End of 'profile_timer.cpp' */

