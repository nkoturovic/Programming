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

    [[ nodiscard ]] constexpr auto to_array() const { 
        return boost::hana::unpack(m_tuple, [](auto... xs) { return std::array{xs...}; });
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

// TODO: Napraviti funkcije koje rade bez dodatnog argumenta npr. filter([]<T>()) 
// koji operisu samo na tipovima koji su prisutni (ignorise vrednost)


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

    std::tuple stt{1.0, 2, std::string{"Hello"}, std::string{"world"}};
    auto fstt = Tuple(std::move(stt))
        .filter([]<class T>(T /* unused */) { return std::is_class<T>(); })
        .transform([](auto x) { /* return x + 42 */return x+x; })
        .to_array();


    fmt::print("{}\n", fstt);
    fmt::print("{}\n", lv.to_std_tuple());

    return 0;
}



// TODO: Refleksija
//// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
// #include <boost/hana/accessors.hpp>
// #include <boost/hana/adapt_struct.hpp>
// #include <boost/hana/assert.hpp>
// #include <boost/hana/core/to.hpp>
// #include <boost/hana/equal.hpp>
// #include <boost/hana/find.hpp>
// #include <boost/hana/first.hpp>
// #include <boost/hana/map.hpp>
// #include <boost/hana/not_equal.hpp>
// #include <boost/hana/optional.hpp>
// #include <boost/hana/pair.hpp>
// #include <boost/hana/string.hpp>
// #include <boost/hana/transform.hpp>
// #include <boost/hana/tuple.hpp>
// #include <string>
// namespace hana = boost::hana;
// namespace ns {
//     struct Person {
//         std::string name;
//         int age;
//     };
// }
// BOOST_HANA_ADAPT_STRUCT(ns::Person,
//     name,
//     age
// );
// // The member names are hana::strings:
// auto names = hana::transform(hana::accessors<ns::Person>(), hana::first);
// BOOST_HANA_CONSTANT_CHECK(
//     names == hana::make_tuple(BOOST_HANA_STRING("name"), BOOST_HANA_STRING("age"))
// );
// int main() {
//     ns::Person john{"John", 30}, bob{"Bob", 40};
//     BOOST_HANA_RUNTIME_CHECK(hana::equal(john, john));
//     BOOST_HANA_RUNTIME_CHECK(hana::not_equal(john, bob));
//     BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("name")) == hana::just("John"));
//     BOOST_HANA_RUNTIME_CHECK(hana::find(john, BOOST_HANA_STRING("age")) == hana::just(30));
//     BOOST_HANA_CONSTANT_CHECK(hana::find(john, BOOST_HANA_STRING("foo")) == hana::nothing);
//     BOOST_HANA_RUNTIME_CHECK(hana::to_tuple(john) == hana::make_tuple(
//         hana::make_pair(BOOST_HANA_STRING("name"), "John"),
//         hana::make_pair(BOOST_HANA_STRING("age"), 30)
//     ));
//     BOOST_HANA_RUNTIME_CHECK(hana::to_map(john) == hana::make_map(
//         hana::make_pair(BOOST_HANA_STRING("name"), "John"),
//         hana::make_pair(BOOST_HANA_STRING("age"), 30)
//     ));
