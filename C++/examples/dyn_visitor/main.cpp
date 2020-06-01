#include <iostream>
#include <type_traits>
#include <concepts>

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>; // not needed as of C++20


/* VISITOR KLASA */
template <typename ...Ts>
struct Visitor;

template <>
struct Visitor<> {
    Visitor() = delete;
    template <typename B, std::invocable<B> Func>
    constexpr static auto visit(Func && f, B &b) {
        return f(b);
    }
};

template <typename D, typename ...Ds> 
struct Visitor<D,Ds...> {
    Visitor() = delete;

    template <typename B, std::invocable<B> Func> requires std::derived_from<D,B>
    constexpr static auto visit(Func && f, B &b) {

        if constexpr (std::is_same_v<std::result_of_t<Func(B)>, void>) {
            if (auto d = dynamic_cast<D*>(&b); d)
                    f(*d);
            else
                Visitor<B,Ds...>::visit(f, b);
        } else {
            if (auto d = dynamic_cast<D*>(&b); d)
                return f(*d);
            else
                return Visitor<B,Ds...>::visit(f, b);
        }
    }
};

/* MOJA HIJERARHIJA */
struct B { 
    virtual ~B() = default;
};

struct D1 : B {};
struct D2 : B {};

int main()
{
    /* IDEJA: Pokusaj imitacije std::visit kao kod std::variant */
    D1 d1;
    B& b = d1;

    auto result = Visitor<D1,D2>::visit(overloaded {
            [](const B& b) { return 0; },
            [](const D1 &d1) { return 1; },
            [](const D2 & d2) { return 2; }
    }, b);

    std::cout << result << std::endl;

    return 0;
}
