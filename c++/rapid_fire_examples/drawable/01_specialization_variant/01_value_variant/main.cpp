#include <cstdio>
#include <vector>
#include <variant>

struct Circle {
    double radius = 1;
};

struct Square {
    double width;
};

// DrawableC
template <typename T>
concept CDrawable = requires (const T &t) {
    { draw(t) };
};

template <typename D>
constexpr void draw(const D&);


template <CDrawable...Ts>
void draw_all(const std::vector<std::variant<Ts...>> &vec) {
    for (const auto &e : vec) {
        std::visit([]<CDrawable D>(const D& d) {
                draw<D>(d); 
        }, e); 
    }
}

int main()
{
    // Static dispatch with draw_all
    //draw_all(cs);

    std::vector<std::variant<Circle, Square>> cs{ 
            Circle{.radius=2.2},
            Square{.width=4.2}
    };

    draw_all(cs);

    return 0;
}

template <>
inline void draw(const Circle &circle) {
    printf("Circle with radius: %lf\n", circle.radius);
}

template <>
inline void draw(const Square &square) {
    printf("Square with width: %lf\n", square.width);
}
