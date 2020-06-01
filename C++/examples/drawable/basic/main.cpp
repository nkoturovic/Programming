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
concept Drawable = requires (const T &t) {
    { draw(t) };
};

/* Drawable without CRTP type info */
struct DrawableI {
    friend void draw(const DrawableI&);
    constexpr virtual ~DrawableI() = default;
private:
    constexpr virtual void draw() const = 0;
};

template <typename D>
constexpr void draw(const D&);

inline void draw(const DrawableI &d) {
    d.draw();
}

template <typename T>
struct DrawableCRTP final : DrawableI {
    constexpr DrawableCRTP(const T& ref) : m_ref(ref) {}
private:
    constexpr void draw() const override {
        ::draw<T>(m_ref);
    }
    const T& m_ref;
};

template <>
inline void draw(const Circle &circle) {
    printf("Circle with radius: %lf\n", circle.radius);
}

template <>
inline void draw(const Square &square) {
    printf("Square with width: %lf\n", square.width);
}

template <typename T> requires requires (T t) { { draw(*t)}; }
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
