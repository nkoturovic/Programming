#include <iostream>
#include <cstdio>

int main()
{

    fprintf(stdout, "Hello word\n");

    std::cout << "Hello world" << std::endl;

    // isto sto i
    std::cout << "Hello world" << '\n';
    std::cout << std::flush;

    return 0;
}


