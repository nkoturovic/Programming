#include <cstdio>
#include <vector>
#include <variant>
#include <span>
#include <type_traits>

template <class D>
struct ToString;

template <typename T>
concept HasToString = requires (const T &t) {
    { ToString<T>::to_string(t) } -> std::convertible_to<const char *>;
};

template <HasToString T>
struct ToString<T*> {
    static const char * to_string(T *t) {
        return ToString<T>::to_string(*t);
    }
};

 template <HasToString ...Ts>
 struct ToString<std::variant<Ts...>> {
     static const char * to_string(const std::variant<Ts...> &var) {
         return std::visit([]<HasToString T> (const T &t) {
                 return ToString<T>::to_string(t); 
         }, var);
     }
 };

template <HasToString T>
const char * to_string(const T &t) { 
    return ToString<T>::to_string(t);
}

struct Circle {
    double radius = 1;
};

struct Square {
    double width;
};

template <>
struct ToString<Circle> {
    static const char * to_string(const Circle&/* */) {
        return "Circle";
    }
};

template <>
struct ToString<Square> {
    static const char * to_string(const Square&/* */) {
        return "Square";
    }
};

template <HasToString T>
void print_all(std::span<T> s) {
    for (const auto &e : s) 
        std::puts(to_string<T>(e));
}

int main()
{
    Circle c{.radius=2.2};
    Square s{.width=4.2};

    std::puts(to_string(s));

    std::array cptrs{ &c, &c, &c};

    print_all<Circle*>(cptrs);

    std::array<std::variant<Circle*, Square*>, 3> vptrs {
        &s, &c, &s
    };

    print_all<std::variant<Circle*,Square*>>(vptrs);

    std::array<std::variant<Circle, Square>, 3> vs {
        std::move(c), std::move(s)
    };

    print_all<std::variant<Circle,Square>>(vs);

    return 0;
}
