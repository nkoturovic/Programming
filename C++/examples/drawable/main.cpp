#include <cstdio>
#include <vector>
#include "shapes.hpp"
#include "drawable.hpp"

template <>
inline void draw(const Circle &circle) {
    printf("Circle with radius: %lf\n", circle.radius);
}

template <>
inline void draw(const Square &square) {
    printf("Square with width: %lf\n", square.width);
}

template <Drawable T>
void draw_all(const std::vector<T> vec) {
    for (const auto e : vec)
        draw(*e);
}

int main()
{
    Circle c{.radius=2.2};
    std::vector<Circle*> cs{ &c, &c, &c };
    // Static dispatch with draw_all
    draw_all(cs);

    DrawableCRTP dc(c);
    Square s{.width=4.2};
    DrawableCRTP ds(s);

    // Dynamic dispatch with draw_all
    std::vector<DrawableI*> vec{ &dc, &ds, &dc, &dc };
    draw_all(vec);

    return 0;
}
