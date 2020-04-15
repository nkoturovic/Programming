#include <cstdio>
#include <stdexcept>
#include <cmath>

template <class G, class F>
constexpr auto compose(G &&g, F &&f) {
    return [g,f](auto ... args) { return g(f(args...)); };
}

template <class G, class F, class ... Hs>
constexpr auto compose(G &&g, F &&f, Hs&& ... hs) {
    return compose(std::forward<G>(g),compose(std::forward<F>(f), std::forward<Hs>(hs)...));
}

template <typename Trafo>
struct trafo_helper {
  Trafo trafo;
  // umesto ovog je funkcija ispod
  template <typename ... Args>
  auto operator()(Args&& ...args) { return trafo(std::forward<Args...>(args)...); }
};

template <typename Trafo>
constexpr auto transform(Trafo &&trafo) {
  return trafo_helper<Trafo>{std::forward<Trafo>(trafo)};
}

template <class F, class G>
constexpr auto operator | (const trafo_helper<F> &&f, const trafo_helper<G> &&g) {
    return transform(compose(g.trafo, f.trafo));
}

constexpr int square(int x) { return x*x; }

constexpr double e_sqrt(double x) { 
    if (x <= 0)
        throw std::runtime_error("Cant apply sqrt value <= 0");
    else 
        return sqrt(x);
}

constexpr double e_divide(double x, double y) { 
    if (x == 0)
        throw std::runtime_error("Cant divide, denominator == 0");
    else 
        return x / y;
}

int main(int, char *argv[]) {

    // Obratiti paznju da je kompajler dovoljno pametan
    // da zna da ce e_sqrt biti pozvana tek nakon square
    // i u stanju je da u potpunosti izbaci izuzetke !!!

    //auto composed = compose ( 
    //        e_sqrt,
    //        square, 
    //        [](int x) { return x+1; }, 
    //        square, 
    //        square
    //);

    auto composed = transform(square)
                  | transform(square)
                  | transform([](int x) { return x+1; })
                  | transform(square)
                  | transform(e_sqrt)
                  ;

    try {
        printf("%lf\n", composed(std::atof(argv[1])));
    } catch (const std::exception &e) {
        puts(e.what());
    }

    return 0;
}
