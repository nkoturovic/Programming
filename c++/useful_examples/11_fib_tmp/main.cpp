#include <iostream>

template<int n>
struct fibonacci
{
  static constexpr int value = fibonacci<n-1>::value + fibonacci<n-2>::value;
};
template<>
struct fibonacci<0>
{
  static constexpr int value = 0;
};
template<>
struct fibonacci<1>
{
  static constexpr int value = 1;
};

int main()
{
    constexpr int fib40 = fibonacci<20>::value;
    std::cout << fib40 << '\n';
    return 0;
}
