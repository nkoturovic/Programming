#include <iostream>
#include <memory>
#include <vector>
#include <variant>

// Helpers
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // not needed as 

// class Shape {
// public:
//     virtual double area() = 0;
// };

struct Square {
    double a;
};

struct Circle {
    double radius;
};

struct ShapeAreaVisitor {
    double operator()(const Square &s) { return s.a*s.a; }
    double operator()(const Circle &s) { return s.radius*s.radius*std::numbers::pi; }
};


int main() {
    std::vector<std::variant<Square, Circle>> shapes { Circle {3.0}, Circle {2.0}, Square {4.0} };
    ShapeAreaVisitor area_vtor{};
    for (const auto &s : shapes) {
        std::cout << std::visit(area_vtor, s) << std::endl;
    }

    for (const auto &s : shapes) {
        std::visit(overloaded{
            [](const Circle &c) { std::cout << c.radius << std::endl; },
            [](const Square &c) { std::cout << c.a << std::endl; }},
            s);
    }

    return 0;
}
