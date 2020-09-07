#include <fmt/format.h>
#include <ranges>
#include <cstdio>

int main()
{
    std::array xs{1,2,3,4,5};

    for (auto x : xs | std::views::filter([](auto x) { return x%3 == 0; }))
        fmt::print("{}\n", x);

    return 0;
}
