#include <string>
#include <iostream>
#include <variant>
#include <functional>
#include <cmath>

template <typename... Ts>
struct print_types;

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // not needed as of C++20

template <typename Left, typename Right>
using Either = std::variant<Left, Right>;

template <typename Ftype, typename Left, typename OldRight>
auto mapM(Ftype &&f, Either<Left, OldRight> &&val) -> Either<Left,typename std::invoke_result<Ftype,OldRight>::type> {
      using Right = typename std::invoke_result<Ftype,OldRight>::type;
      return std::visit(overloaded {
            [](Left && arg) -> Either<Left,Right>        { return std::forward<Left>(arg); },
            [&f](OldRight && arg) -> Either<Left, Right> { return std::invoke(std::forward<Ftype>(f), std::forward<OldRight>(arg)); }
      }, std::forward<Either<Left,OldRight>>(val));
}

template <typename Ftype, typename Left, typename OldRight>
auto bindM(Either<Left,OldRight> val, Ftype &&f) -> typename std::invoke_result<Ftype,OldRight>::type {
      using ResultType = typename std::invoke_result<Ftype,OldRight>::type;
      return std::visit(overloaded {
            [](Left && arg) -> ResultType        { return std::forward<Left>(arg); },
            [&f](OldRight && arg) -> ResultType  { return std::invoke(std::forward<Ftype>(f), std::forward<OldRight>(arg)); }
      }, std::forward<Either<Left,OldRight>>(val));
}

template <class G, class F>
constexpr auto compose (G &&g, F &&f) {
    return [g,f](auto ... args) { return f(g(args...)); };
}

template <class G, class F, class ... Hs>
constexpr auto compose (G &&g, F &&f, Hs&& ... hs) {
    return compose(std::forward<G>(g), compose(std::forward<F>(f), std::forward<Hs>(hs)...));
}

template <class G, class F>
constexpr auto composeM (G &&g, F &&f) {
    return [g,f](auto ... args) { 
        auto gret = g(args...);
        if(auto pval = std::get_if<1>(&gret)) {
            return std::invoke(f, *pval);
        } else {
            return gret;
        }
    };
}

template <class G, class F, class ... Hs>
constexpr auto composeM(G &&g, F &&f, Hs&& ...hs) {
    return composeM(std::forward<G>(g), composeM(std::forward<F>(f), std::forward<Hs>(hs)...));
}


Either<std::string, double> safe_sqrt(double x) {
    if ( x <= 0 )
        return "Broj <= 0: Ne mogu uraditi sqrt";
    else 
        return sqrt(x);
}

int main()
{
    Either<std::string, int> val { 16 };
    auto comp = composeM(safe_sqrt, 
                         safe_sqrt, 
                         safe_sqrt);

    auto r = bindM(val, comp);
    std::visit([](const auto &x) { std::cout << x << std::endl; }, std::move(r));
}
