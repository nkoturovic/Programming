#include <iostream>

template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };
 
template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };
 
template< class T > struct remove_volatile             { typedef T type; };
template< class T > struct remove_volatile<volatile T> { typedef T type; };



template <typename T>
struct print_type;

int main() {
    remove_cv<const int>::type x = 3;
    // print_type<remove_cv<const int>::type>{};
    x = 4;
    std::cout << x << '\n';
}
