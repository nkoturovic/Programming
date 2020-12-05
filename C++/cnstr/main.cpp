#include <fmt/format.h>
#include <fmt/ranges.h>
#include <tuple>
#include <boost/hana.hpp>
#include <boost/hana/ext/std/tuple.hpp>
#include <range/v3/all.hpp>

namespace hana = boost::hana;

template <typename ...Ts>
class Tuple {
    boost::hana::tuple<Ts...> m_tuple; 

    template <typename ...Hs>
    [[ nodiscard ]] constexpr static Tuple<Hs...> from_hana_tuple(hana::tuple<Hs...> &&h) {
        return hana::unpack(std::move(h), [](Hs&& ...hs) { return Tuple<Hs...>{std::move(hs)...}; });
    }
public:
    constexpr Tuple(Ts&&... ts) : m_tuple(std::move(ts)...) {} 
    constexpr Tuple(std::tuple<Ts...>&& t) : m_tuple(boost::hana::to<hana::tuple_tag>(std::move(t))) {} 

    template <typename Func>
    [[ nodiscard ]] constexpr auto filter(Func&& func) const { 
        return Tuple::from_hana_tuple(boost::hana::filter(std::move(m_tuple), std::forward<Func>(func)));
    }

    template <typename Func>
    [[ nodiscard ]] constexpr auto transform(Func&& func) const { 
        return Tuple::from_hana_tuple(boost::hana::transform(std::move(m_tuple), std::forward<Func>(func)));
    }

    template <typename Acc, typename Func>
    [[ nodiscard ]] constexpr Acc&& accumulate(Acc &&acc, Func &&func) const {
        boost::hana::for_each(std::move(m_tuple), [&]<typename X>(X&& x) {
            acc = func(std::forward<Acc>(acc), std::forward<X>(x));
        });
        return std::forward<Acc>(acc);
    }

    [[ nodiscard ]] constexpr std::tuple<Ts...> to_std_tuple() const {
        return hana::unpack(std::move(m_tuple), []<class ...Xs>(Xs&& ...xs) { return std::tuple{std::forward<Xs>(xs)...}; });
    }

    template <typename Func>
    void for_each(Func&& func) const { boost::hana::for_each(std::move(m_tuple), std::forward<Func>(func)); }

};


// TODO: Da li koristiti hana::type ili Cnstr{} za prosledjivnaje vrednosti???
// Ili nekako smisliti prosledjivanje putem template parametra <Cnstr>, ali to 
// Ili cak custom type<T>


int main() {

   // auto print_fn = [](const auto& e) { std::visit([](const auto& e) { fmt::print("{}\n", e); }, e); };
   // for (const auto &e : to_range(t))
   //     print_fn(e);

    constexpr auto lv = Tuple{2, 4.0};
    constexpr auto rs = lv
        .filter([]<class T>(T /* unused */) { return std::is_floating_point<T>(); })
        .transform([](auto x) { /* return x + 42 */return x*x; })
        .accumulate(
            0,
            [](auto acc, auto x) {
                return acc + x;
            }
        );

    fmt::print("{}\n", rs);
    fmt::print("{}\n", lv.to_std_tuple());

    std::tuple stt{1.0, 2, std::string{"Hello"}};
    auto fstt = Tuple(std::move(stt))
        .filter([]<class T>(T /* unused */) { return std::is_floating_point<T>(); })
        .transform([](auto x) { /* return x + 42 */return x*x; });


    fmt::print("{}\n", fstt.to_std_tuple());
    fmt::print("{}\n", lv.to_std_tuple());

    return 0;
}
