
/**
 * 
 * @File   : modern-literal.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-14 18:29    (+0800)   
 * @Brief  :  
 * 
**/

#include <cstdio> // sprintf()
#include <iostream>
#include <string>
#include <complex>
#include <chrono>
#include <stdexcept>    // domain_error

#if __cplusplus < 201100
#  error "C++11 or better is required"
#endif

using namespace std;

// user-define-literal MUST start with underline:
long double operator "" _mol( long double x) { return 6.02e23 * x;}
// can be used for constexpr if simple enough:
constexpr unsigned long long operator "" _dozen( unsigned long long n) { return 12 * n;}

// use with class:
struct VideoTimestamp {
    unsigned seconds;
    operator string() const {
        char str[ 128];
        unsigned    hour = seconds / ( 60*60),
                    min = ( seconds / 60) % 60,
                    sec = seconds % 60;
        sprintf( str, "%02d:%02d:%02d", hour, min, sec);
        return str;
    }
    VideoTimestamp operator+( VideoTimestamp const &another) const { return VideoTimestamp{ seconds+another.seconds};}
    VideoTimestamp operator-( VideoTimestamp const &another) const {
        if ( seconds >= another.seconds)
            return VideoTimestamp{ seconds - another.seconds};
        else
            return VideoTimestamp{ another.seconds - seconds};
    }
}; // struct VideoTimestamp

VideoTimestamp operator "" _ts( char const *str, size_t size) {
    string s( str, size);
    auto l = s.length();
    if ( l < 4 || s[ l-3] != ':')
        goto WRONG_FORMAT;
    else if ( l >= 6 && s[ l-6] != ':')
        goto WRONG_FORMAT;
    try {
        unsigned    hour = l < 6 ? 0 : stoul( s.substr( 0, l-6)),
                    min  = stoul( s.substr( max( (int)l-5, 0), 2)),
                    sec  = stoul( s.substr( l-2, 2));
        return VideoTimestamp{ hour*60*60 + min*60 + sec};
    } catch ( exception const &e) {
        goto WRONG_FORMAT;
    }
WRONG_FORMAT:
        throw domain_error( s + " is not valid timestamp!");
}


constexpr char ALIGN[] = "                                    ";
#define SHOW( x) cout << #x << " :" << (ALIGN+sizeof( #x)) << ( x) << endl

int main() {
    SHOW( 1.5_mol);
    SHOW( 20_dozen);
    SHOW( string( "5:41"_ts - "2:02:34"_ts));

#if __cplusplus > 201400

    // standard-defined-literals:

    using namespace std::complex_literals;
    SHOW( 5.0+2i);      // constexpr complex<double> operator""i( unsigned long long n);
    SHOW( 5.0f-1.2if);  // constexpr complex<float> operator""i( long double n);
    SHOW( 0.2il);       // constexpr complex<long double> operator""i( long double n);

    using namespace std::chrono_literals;
    SHOW( ( 5h - 4min).count());    // return number of minutes

#   if __cplusplus > 202000 // need Duration::operator<<() from C++20
    SHOW( 3s + 210ms);
    using chrono::duration_cast;
    using chrono::seconds;
    SHOW( duration_cast<seconds>(1000000us));
    SHOW( -99ns);
#   endif // c++20

    using namespace std::string_literals;
    SHOW( "123"s.length()); // convert c-str literal to c++ string

#endif // c++14

    return 0;
}


/*  End of 'modern-literal.cpp' */

