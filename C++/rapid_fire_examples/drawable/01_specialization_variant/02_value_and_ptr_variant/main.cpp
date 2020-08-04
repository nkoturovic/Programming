
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
void draw(const D&);


template <CDrawable ...Ts>
void draw_all(const std::vector<std::variant<Ts...>> &vec) {
    for (auto &&e : vec) {
        std::visit([]<CDrawable D>(D&& d) {
            using type = std::remove_cvref_t<D>;
            if constexpr (std::is_pointer_v<type>)
                draw<std::remove_pointer_t<type>>(*d); 
            else
                draw<type>(d); 
        }, e); 
    }
}

int main()
{
    // Static dispatch with draw_all
    //draw_all(cs);

    Circle c{.radius=2.2};
    Square s{.width=4.2};
 
    std::vector<std::variant<Circle, Circle*, Square, Square*>> cs{ 
        &c, Circle{.radius=3.2}, &s, Square{.width=5.2}
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
