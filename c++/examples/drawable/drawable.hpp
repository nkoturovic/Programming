#ifndef DRAWABLE_H
#define DRAWABLE_H

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


#endif
