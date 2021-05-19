#include <iostream>
#include <range/v3/all.hpp>
#include <concepts/concepts.hpp>

template <class T>
bool even(T x) requires concepts::integral<T> {
    return x % 2 == 0;
}

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

    for (const auto &v : ranges::views::iota(1, 21))
        std::cout << v << ' ';

    std::cout << '\n';
    std::cout << even(2) << '\n';

    return 0;
}
