#include <iostream>
#include <cmath>
#include <QList>
#include <QtConcurrent/QtConcurrentFilter>
#include <QtConcurrent/QtConcurrentMap>

void filter_example()
{
    std::vector<int> xs(10);
    std::iota(xs.begin(), xs.end(), 1);

    QFuture<int> evens = QtConcurrent::filtered(xs, [](int x) { return x % 2 == 0; });

    for (const auto& e : evens.results())
        std::cout << e << '\n';

    std::cout << std::flush;
}

void map_example() {
    std::vector<int> xs(10);
    std::iota(xs.begin(), xs.end(), 1);

    using ftype = int(*)(int);
    ftype func = [](int x) { return x*x; };
    QFuture<int> squares = QtConcurrent::mapped(xs, func);

    for (const auto& e : squares.results())
        std::cout << e << '\n';

    std::cout << std::flush;

}

void map_reduce_example() {
    std::vector<int> xs(10);
    std::iota(xs.begin(), xs.end(), 1);
    // TODO
}


int main(int argc, char * argv[]) {

    const char * sep = "-------------------------------\n";
    if (argc != 2) {
        std::cerr << "Pogresan broj argumenata" << "\n";
        std::cerr << sep;
        std::cerr << "f - filter_example()\n";
        std::cerr << "m - map_example()\n";
        std::cerr << "b - map_reduce_example()\n";
        std::cerr << sep;
        exit(EXIT_FAILURE);
    }

    switch(argv[1][0]) {
        case 'f': filter_example(); break;
        case 'm': map_example(); break;
        case 'b': map_reduce_example(); break;
        default : std::cerr << "Pogresan argument: " << argv[1][0] << '\n';
                  exit(EXIT_FAILURE);
    }

    return 0;
}
