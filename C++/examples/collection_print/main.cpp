#include <iostream>
#include <map>
#include <vector>
#include <functional>

template <typename It>
void print(
    It begin, It end, std::string delimiter = ", ",
    std::ostream& out = std::cout,
    std::function<std::ostream&(std::ostream&,
                                typename std::iterator_traits<It>::value_type)>
        printElFunc = [](std::ostream& out,
                         typename std::iterator_traits<It>::value_type val)
        -> std::ostream& { return out << val; }) {
    It it;
    for (it = begin; it != end;) {
        printElFunc(out, *it);
        if (++it != end) out << delimiter;
    }
}

template <typename Collection>
void print(
    Collection collection, std::string delimiter = ", ",
    std::ostream& out = std::cout,
    std::function<std::ostream&(std::ostream&, typename Collection::value_type)>
        printElFunc = [](std::ostream& out, typename Collection::value_type val)
        -> std::ostream& { return out << val; }) {
    return print(std::begin(collection), std::end(collection), delimiter, out,
                 printElFunc);
}

int main() {
    {
        std::vector xs{1, 2, 3, 4, 5};
        print(xs);
        std::cout << '\n';

        std::vector ys{"2", "da", "hello", "there", "dddd"};
        print(ys);
        std::cout << '\n';

        std::map<unsigned, std::string> dict{{1u, "da"}, {2u, "ne"}};
        auto printPair = [](std::ostream& out, auto pair) -> std::ostream& {
            return out << '(' << pair.first << ", " << pair.second << ')';
        };

        print(dict, ",", std::cout, printPair);
        std::cout << '\n';
    }

    /* Iterator versions */
    {
        std::vector xs{1, 2, 3, 4, 5};
        print(std::cbegin(xs), std::cend(xs));
        std::cout << '\n';

        std::vector ys{"2", "da", "hello", "there", "dddd"};
        print(std::cbegin(ys), std::cend(ys));
        std::cout << '\n';

        std::map<unsigned, std::string> dict{{1u, "da"}, {2u, "ne"}};
        auto printPair = [](std::ostream& out, auto pair) -> std::ostream& {
            return out << '(' << pair.first << ", " << pair.second << ')';
        };

        print(std::cbegin(dict), std::cend(dict), ",", std::cout, printPair);
        std::cout << '\n';

        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        print(std::cbegin(arr), std::cend(arr));
        std::cout << '\n';

        constexpr std::pair matrix_size{3, 3};
        int matrix[matrix_size.first][matrix_size.second] = {
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        auto print_matrix_row = [](std::ostream& out,
                                   int* row) -> std::ostream& {
            print(row, row + matrix_size.second, " ");
            return out;
        };

        print(std::begin(matrix), std::end(matrix), "\n", std::cout,
              print_matrix_row);
        std::cout << '\n';
    }

    return 0;
}
