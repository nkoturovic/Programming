#include <fmt/format.h>
#include <fmt/ranges.h>
#include "constraints.hpp"
#include <string>

int main()
{
    using ltype = Not<AnyOf<Length<1,3>, Length<5,9>>>;
    fmt::print("{}\n", ltype::name);
    fmt::print("{}\n", ltype::description);
    fmt::print("{}\n", ltype::is_satisfied("hello world"));

    Field<std::string, AnyOf<Length<1,3>, Length<9,14>>> hello_world({"Hello world"});
    Field<std::string, AnyOf<Length<1,3>, Length<9,14>>> hello({"Hello"});

    try {
        fmt::print("{}\n", hello_world.value());
    } catch (const std::exception &e) {
        fmt::print("{}\n", e.what());
    }

    if (hello_world.constraints_satisfied())
        fmt::print("{}\n", *hello_world);
    else
        fmt::print("Some constraints are unsatisfied\n");

    auto print_if_satisfies = [](const auto &c) {
        if (c.has_value() && c.constraints_satisfied())
            fmt::print("{}\n", *c);
        else 
            fmt::print("Some constraints are unsatisfied\n");
    };

    print_if_satisfies(hello_world);

    constexpr auto get_unsatisfied_constraints = [](const auto &field) {
        return field.accumulate_constraints(
            std::vector<std::string>{}, 
            []<Cnstr C>(std::vector<std::string> &&acc, const auto& field_ref) {
                if (!C::is_satisfied(field_ref))
                    acc.emplace_back(C::name);
                return std::move(acc);
            });
    };

    //constexpr auto to_string = [get_unsatisfied_constraints](const auto &field) -> std::string {
    //    if (!field.has_value()) {
    //        return field.is_required ? "No value but required" : "No value but not required";
    //    } else if (field.has_value() && !field.constraints_satisfied()) {
    //        return fmt::format("{}", get_unsatisfied_constraints(field));
    //    } else {
    //        return "Sucess";
    //    }
    //};

    // fmt::print("hello_world: {}\n", to_string(hello_world));
    // fmt::print("hello: {}\n", to_string(hello));

    // hello_world = {};
    // fmt::print("hello: {}\n", to_string(hello_world));

    // hello = {};
    // fmt::print("hello: {}\n", to_string(hello));

    return 0;
}
