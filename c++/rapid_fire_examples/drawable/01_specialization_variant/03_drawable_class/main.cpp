#include <cstdio>
#include <vector>

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

class Drawable {
    friend void draw(const Drawable&);
    void * m_instance;

    using draw_ftype = void(*)(void*);
    draw_ftype m_draw_func;

    /* This function is private because we       *
     * want user to use draw(something) instead  *
     * of something.draw();                      */
    void draw() const {
        m_draw_func(m_instance);
    }

public:
    template <typename T>
    Drawable(T &t_ptr) : m_instance(&t_ptr), m_draw_func(reinterpret_cast<void(*)(void*)>(::draw<T>)) {}
    const Drawable& operator*() const { return *this; }
};

void draw(const Drawable &d) {
    d.draw();
}

template <>
void draw(const Circle &circle) {
    printf("Circle with radius: %lf\n", circle.radius);
}

template <>
void draw(const Square &square) {
    printf("Square with width: %lf\n", square.width);
}

template <CDrawable T>
void draw_all(const std::vector<T> vec) {
    for (const auto e : vec)
        draw(*e);
}

int main()
{
    // Static dispatch with draw_all
    //draw_all(cs);
    Circle c{.radius=2.2};
    std::vector<Circle*> cs{ &c, &c, &c };
    draw_all(cs);

    Square s{.width=4.2};
    // Dynamic dispatch with draw_all
    std::vector<Drawable> vec{c, s, c, s};
    draw_all(vec);

    return 0;
}
