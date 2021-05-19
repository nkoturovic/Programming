#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <cstdio>

int main()
{
    namespace views = ranges::views;

    std::array xs{1,2};
    std::array ys{"hello", "world"};

    for (const auto &[x,y] : views::zip(xs,ys))
        fmt::print("{} -> {}\n", x, y);

    return 0;
}
