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


template <CDrawable ...Ds>
struct DrawableVariant : public std::variant<Ds...> {
    using std::variant<Ds...>::variant;

    void draw() const {
        std::visit([]<CDrawable D>(D const& d) {
            ::draw<D>(d);
        }, static_cast<std::variant<Ds...>const &>(*this));
    }
};


template <CDrawable...Ts>
void draw_all(const std::vector<DrawableVariant<Ts...>> &vec) {
    for (const auto &e : vec) {
        e.draw();
    }
}

int main()
{
    // Static dispatch with draw_all
    //draw_all(cs);

    std::vector<DrawableVariant<Circle, Square>> cs{ 
            Circle{.radius=2.2},
            Square{.width=4.2}
    };

    draw_all(cs);

    return 0;
}

template <>
void draw(const Circle &circle) {
    printf("Circle with radius: %lf\n", circle.radius);
}

template <>
void draw(const Square &square) {
    printf("Square with width: %lf\n", square.width);
}
