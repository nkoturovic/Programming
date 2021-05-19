#include <cstdio>
#include <vector>


struct Drawable {
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
};

struct Circle final : Drawable {
    double radius = 1;
    void draw() const override {
        printf("Circle with radius: %lf\n", radius);
    }
};

struct Square final : Drawable {
    double width;
    void draw() const override {
        printf("Square with width: %lf\n", width);
    }
};

template <typename T> requires requires (T t) { { t->draw() };}
void draw_all(const std::vector<T> &vec) {
    for (const auto &e : vec)
        e->draw();
}

int main()
{
    Circle c;
    c.radius = 2.2;
    Square s;
    s.width = 4.2;

    std::vector<Drawable*> vec{ &c, &s };
    draw_all(vec);
   
    return 0;
}
