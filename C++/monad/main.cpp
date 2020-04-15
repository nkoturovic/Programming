#include <string>
#include <iostream>
#include <variant>
#include <functional>
#include <cmath>

template <typename... Ts>
struct print_types;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename Left, typename Right>
using Either = std::variant<Left, Right>;

template <typename Ftype, typename Left, typename OldRight>
constexpr auto mapM(Ftype &&f, Either<Left, OldRight> &&val) -> Either<Left, std::invoke_result_t<Ftype,OldRight>> {
      using Right = std::invoke_result_t<Ftype,OldRight>;
      return std::visit(overloaded {
            [](Left && arg) -> Either<Left,Right>        { return std::forward<Left>(arg); },
            [&f](OldRight && arg) -> Either<Left, Right> { return std::invoke(std::forward<Ftype>(f), std::forward<OldRight>(arg)); }
      }, std::forward<Either<Left,OldRight>>(val));
}

/* Ovde problem dedukcija povratne vrednosti ???????? */
template <typename Ftype, typename Left, typename OldRight>
constexpr auto bindM(Either<Left,OldRight> &&val, Ftype &&f) -> std::invoke_result_t<Ftype,OldRight> { 
      using ResultType = std::invoke_result_t<Ftype,OldRight>;
      //print_types<ResultType>{};
      return std::visit(overloaded {
            [](Left && arg) -> ResultType        { return { std::forward<Left>(arg) }; },
            [&f](OldRight && arg) -> ResultType  { return std::invoke(std::forward<Ftype>(f), std::forward<OldRight>(arg)); }
      }, std::forward<Either<Left,OldRight>>(val));
}

template <class G, class F>
constexpr auto compose(G &&g, F &&f) {
    return [g,f](auto ... args) { return g(f(args...)); };
}

template <class G, class F, class ... Hs>
constexpr auto compose(G &&g, F &&f, Hs&& ... hs) {
    return compose(std::forward<G>(g), compose(std::forward<F>(f), std::forward<Hs>(hs)...));
}

template <class G, class F>
constexpr auto composeM(G &&g, F &&f) {
    return [g,f]<typename ...Args>(Args ... args) {
        auto fret = f(args...);
        // using ret_type = Either<std::decay_t<decltype(std::get<0>(gret))>, std::decay_t<decltype(std::get<1>(gret))>>;

        if(auto pval = std::get_if<1>(&fret)) {
            // return ret_type { std::get<1>(std::invoke(f, std::move(*pval))) };
            //return ret_type { std::invoke(f, std::move(*pval)) };
            return std::invoke(g, std::move(*pval));
        } else {
            // Ako bi uspeo da ubacim ovde Either
             return decltype(std::invoke(g, std::get<1>(fret))){ std::get<0>(fret) };
            // return ret_type { std::get<0>(gret) };
        }
    };
}

template <class G, class F, class ... Hs>
constexpr auto composeM(G &&g, F &&f, Hs&& ...hs) {
    return composeM(std::forward<G>(g), composeM(std::forward<F>(f), std::forward<Hs>(hs)...));
}


// Omogucava sintaksu bez transform (da li to zelimo?)
// template <class F, class Left, class Right>
// constexpr auto operator | (Either<Left, Right> &&val, F &&f) {
//     return bindM(std::forward<Either<Left,Right>>(val), std::forward<F>(f));
// }

template <typename Trafo>
struct trafo_helper {
  Trafo trafo;
  // umesto ovog je funkcija ispod
  //template <typename ... Args>
  //auto operator()(Args...args) { return trafo(args...); }
};

template <typename Trafo>
constexpr auto transform(Trafo &&trafo) {
  return trafo_helper<Trafo>{std::forward<Trafo>(trafo)};
}

// Nije neophodno (treba ili ovo ili operator () )
template <class F, class Left, class Right>
constexpr auto operator | (Either<Left, Right> &&val, trafo_helper<F> &&t) {
    return bindM(std::forward<Either<Left,Right>>(val), std::move(t.trafo));
}

template <class F, class G>
constexpr auto operator | (trafo_helper<F> &&f, trafo_helper<G> &&g) {
    return transform(composeM(std::move(g.trafo), std::move(f.trafo)));
}

// Standard without trafo
// template <class F, class G>
// constexpr auto operator | (F &&f, G &&g) {
//     return composeM(std::forward<G>(g), std::forward<F>(f));
// }

Either<std::string, double> safe_sqrt(double x) {
    if ( x <= 0 )
        return "Broj <= 0: Ne mogu naci koren broja " +
                std::to_string(x);
    else 
        return sqrt(x);
}

Either<std::string, double> safe_div(double x, double y) {
    if ( y == 0 )
        return "Imenilac == 0: Ne mogu podeliti " 
                + std::to_string(x) + " sa " 
                + std::to_string(y);
    else 
        return x / y;
}

int main()
{
    Either<std::string, int> val1 { 1024 };

    // Lenjo
    auto result = Either<std::string, int> { -222 }
                | transform([](auto x) -> Either<std::string,double> { return x + 20.0; })
                | transform([](auto x) { return safe_div(256,x); })
                | transform(safe_sqrt);

    // Nije lenjo
    auto result1 = Either<std::string, int> { -333 }
                 | transform([](auto x) -> Either<std::string,double> { return x + 20.0; })
                 | transform([](auto x) { return safe_div(256,x); })
                 | transform(safe_sqrt)
                 ;

    auto c1 = composeM([](auto x) -> Either<std::string, double> { return x + 3.3; },
                       safe_sqrt);
                       
    auto c2 = transform(safe_sqrt)
            | transform([]<typename T>(T x) -> Either<std::string, T> { return x + 3; })
            ;

    Either<std::string, double> num { 1024.0 };
    //auto r = bindM(std::move(num), c1);
    auto r = std::move(num) | std::move(c2);

    std::visit([](const auto &x) { std::cout << x << std::endl; }, result);
    std::visit([](const auto &x) { std::cout << x << std::endl; }, r);

    return 0;
}
