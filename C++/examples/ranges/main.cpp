#include <iostream>
#include <range/v3/all.hpp>

int main()
{
    std::vector xs {5,3,4,1,2};
    auto is_even = [](auto x) -> bool { return x % 2 == 0; };
    auto even_xs = ranges::views::filter(xs, is_even);
    std::vector ys = ranges::to_vector(even_xs);

    auto rng_printer = [](const auto &x){ std::cout << x << " ";};
    ranges::for_each(even_xs, rng_printer);
    std::cout << '\n';

    ranges::sort(xs);
    ranges::for_each(xs, rng_printer);

    return 0;
}
