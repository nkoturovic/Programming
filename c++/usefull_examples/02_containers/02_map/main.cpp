#include <fmt/format.h>
#include <fmt/ranges.h>
#include <map>
#include <string>

const static std::map<const char *, double> prices = {
    {"apple", 233.00},
    {"orange", 133.00},
    {"bannana", 100.00},
};

int main() {

    for (const auto &[k,v] : prices) {
        fmt::print("{} -> {}\n", k, v);
    }

    // safe access
    auto it = prices.find("apple");
    if (it != prices.end())
        fmt::print("Found apple: {}\n", *it);

    return 0;
}
