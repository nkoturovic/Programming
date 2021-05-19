#include <concepts>
#include "fmt/format.h"
#include "fmt/ranges.h"
#include <string_view>
#include <boost/hana.hpp>

template <class C>
concept NamedConstraint = requires { 
    { C::name } -> std::convertible_to<std::string_view>;
    { C::description } -> std::convertible_to<std::string_view>;
};

template <class C>
concept ValueCnstr = NamedConstraint<C>; // TODO is satisfied

template <class C>
concept ManualCnstr = NamedConstraint<C>; // TODO Handle

template <class C>
concept Cnstr = NamedConstraint<C> || ValueCnstr<C> || ManualCnstr<C>;

struct Dummy {
    static constexpr const char * name = "Dummy";
    static constexpr const char * description = "Dummy Constraint";
};

struct Required {
};

template <ValueCnstr C, ValueCnstr ...Cs>
struct AnyOf {
    inline static std::string name = "AnyOf<" + (C::name + ... + ("," + Cs::name)) + ">";
    inline static std::string description = "(" + (C::description + ... + (") or (" + Cs::description + ")"));
    constexpr static bool is_satisfied(auto val) {
        return (C::is_satisfied(val) || ... || Cs::is_satisfied(val));
    }
};

template <ValueCnstr C>
struct Not {
    inline static std::string name = "Not<" + C::name + ">";
    inline static std::string description = "Not(" + C::description + ")";
    constexpr static auto is_satisfied(auto val) {
        return !C::is_satisfied(val);
    }
};

template<size_t from_ = 0, size_t to_ = from_>
struct Length { 
    constexpr static size_t from = from_;
    constexpr static size_t to = to_;
    inline static std::string name = fmt::format("Length<{},{}>", from, to);
    inline static std::string description = fmt::format("Length should be from {} to {}", from, to);

    constexpr static bool is_satisfied(std::string_view s) {
        return (s.length() >= from) && (s.length() <= to);
    }
};

template<size_t from_ = 0, size_t to_ = from_>
struct Between {
    constexpr static size_t from = from_;
    constexpr static size_t to = to_;
    inline static std::string name = fmt::format("Between<{},{}>", from, to);
    inline static std::string description = fmt::format("Value should be between {} and {}", from, to);

    template <std::totally_ordered T>
    constexpr static bool is_satisfied(T t) {
        return (t >= from) && (t <= to);
    }
};

template <class T>
struct Unique {
    constexpr static const char * name = "Unique";
    constexpr static const char * description = "Field should be unique";
    // constexpr static bool is_satisfied() { return T::manual_cnstr_map[type<Unique>](); };
    // TODO: Think how to make this, something like Map of ManualCnstr -> IsSatisfied() in Field Type!
    // field.manual_cnstr_map.emplace(true) // or field.manual_cnstr_map.emplace([]() { return do_something(); )
};

template <class T, Cnstr ... Ts>
struct Field : std::optional<T> {
    constexpr static auto constraints = boost::hana::tuple_t<Ts...>;
    
    constexpr bool constraints_satisfied() const {
        return boost::hana::all_of(constraints, [&]<class X>(X x) {
            if constexpr (ValueCnstr<typename X::type>)
                 return X::type::is_satisfied(**this);
            else return true;
        });
    }

    template <typename Acc>
    [[ nodiscard ]] Acc&& accumulate_constraints(Acc &&acc, auto acc_func) const {
        boost::hana::for_each(constraints, [&]<typename C>(C& c) {
            acc = acc_func.template operator()<typename C::type>(std::forward<Acc>(acc), **this);
        });
        return std::forward<Acc>(acc);
    }
};
