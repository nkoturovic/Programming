#include <iostream>

class S {
public:
    S() { std::cout << "Default constructor called" << std::endl; }        // Ctor

    // Rule of 5
    S(const S &) { std::cout << "Copy constructor called" << std::endl; }
    S(const S &&) { std::cout << "Move constructor called" << std::endl; }
    S& operator=(const S &) { std::cout << "Assignment operator called" << std::endl; return *this; }
    S& operator=(S &&) noexcept {  std::cout << "Move-Assignment operator called" << std::endl; return *this; }
    ~S() noexcept = default;                    // 3/5: Dtor
};


// void f(S s) {
//     S copy = std::move(s);
// }

void f(S &&s) {
    S copy = std::move(s);
}

int main() {
    S s;
    f(std::move(s));
    
    // playing with `s` may cause undefined behaviour

    return 0;
}
