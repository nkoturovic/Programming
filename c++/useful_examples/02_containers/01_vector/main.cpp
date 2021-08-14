#include <fmt/format.h>
#include <fmt/ranges.h>
#include <vector>
#include <string>
#include <ranges>

int main() {
    std::vector xs{1,2,3,4,5};
    
    for (const auto &x : xs) 
        fmt::print("{}\n", x);

    auto joined_view = fmt::join(xs, ",");
    fmt::print("{}\n", fmt::to_string(joined_view));

    auto is_odd = [](auto x) { return x % 2 == 1; };

    for (auto x : xs | std::views::filter(is_odd)) {
        fmt::print("{}\n", x);

    }

    return 0;
}
