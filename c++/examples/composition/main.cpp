#include <cstdio>
#include <stdexcept>
#include <cmath>
#include "composition.hpp"

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

    auto composed = rs::transform(square)
                  | rs::transform(square)
                  | rs::transform([](int x) { return x+1; })
                  | rs::transform(square)
                  | rs::transform(e_sqrt)
                  ;

    try {
        printf("%lf\n", composed(std::atof(argv[1])));
    } catch (const std::exception &e) {
        puts(e.what());
    }

    return 0;
}
