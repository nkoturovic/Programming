#include <utility> 

template <class G, class F>
constexpr auto compose (G &&g, F &&f) {
    return [g,f](auto ... args) { return g(f(args...)); };
}

template <class G, class F, class ... Hs>
constexpr auto compose (G &&g, F &&f, Hs&& ... hs) {
    return compose(std::forward<G>(g), compose(std::forward<F>(f), std::forward<Hs>(hs)...));
}

constexpr int square(int x) { return x*x; }
constexpr int sum(int x,int y) { return x+y; }

int main() {

    constexpr auto r = compose(square, square, square, sum);
    return r(1,3);
}
