#include <fmt/format.h>
#include <ranges>
#include <cstdio>

int main()
{
    std::array xs{1,4};

    for (auto x : xs | std::views::transform(sqrt))
        fmt::print("{}\n", x);

    return 0;
}
