#include <iostream>
#include <type_traits>

// There is alternative to SFINAE - tag dispatch, hidden from user 
// Another alternative may be strong types in some cases

// Helper function
template <bool condition=false>
inline consteval void static_check() { static_assert(condition); };


#define SFINAE_EX 1

// https://en.cppreference.com/w/cpp/feature_test
#ifndef __cpp_lib_concepts
    #if SFINAE_EX == 1 // enable_if in template argument
        template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        T f(T t) {
            return t * t;
        }

        template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
        T f(T t) {
            return t * t * t;
        }
    #elif SFINAE_EX == 2 // enable_if in return type
        template<typename T>
        std::enable_if_t<std::is_integral_v<T>, T> f(T t) {
            return t * t;
        }

        template<typename T>
        std::enable_if_t<std::is_floating_point_v<T>, T> f(T t) {
            return t * t * t;
        }
    #elif SFINAE_EX == 3 // enable_if in function argument
         // This example might look like it'is not working because
        // it's ambigous but, is_integral<T> and is_floating<T> are two
        // different classes, we could use !is_integral<T> it would also work
        template<typename T>
         // same as: std::enable_if_t<std::is_integral_v<T>, void> *
         // is just common to use: void * = nullptr 
         // because it's rarely missused
         T f(T t, std::enable_if_t<std::is_integral_v<T>>* = nullptr) {
            return t * t;
        }

        template<typename T>
       T f(T t, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr) {
            return t * t * t;
        }
    #endif

    // Alternative (all inside single function)
    template <class T>
    T g(T t) {
        if constexpr (std::is_integral_v<T>) {
            return t * t;
        } else if constexpr (std::is_floating_point_v<T>) {
            return t * t * t;
        } else {
            // cpp20
            // []<bool c = false> { static_assert(c, "no match"); }();

            static_check<std::is_floating_point_v<T> || std::is_integral_v<T>>();
            // static_assert(std::is_floating_point_v<T> 
            //                || std::is_integral_v<T>, 
            //               "Type not supported");

        }
    }

#else // c++20 concepts version
    #include <concepts>

    template <typename T>
    T f(T t) requires std::is_integral_v<T> {
        return t * t;
    }

    template <typename T>
    concept Floating = std::is_floating_point_v<T>;

    template <Floating T>
    T f(T t) {
        return t * t * t;
    }

    // Alternative (all inside single function)
    template <class T>
    T g(T t) {
        if constexpr (std::is_integral_v<T>) {
            return t * t;
        } else if constexpr (Floating<T>) {
            return t * t * t;
        } else {
            []<bool c = false>() { static_assert(c, "Invalid type"); }();
        }
    }
#endif


int main() {
    std::cout << f(2u) << '\n';
    std::cout << f(23) << '\n';
    std::cout << f(2.2) << '\n';
    std::cout << f(2.12f) << '\n';
    std::cout << g(2.12f) << '\n';
    //std::cout << g("h") << '\n';
}
