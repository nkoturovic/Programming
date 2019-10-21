#include <iostream>
#include <memory>
#include "shared_ptr.hpp"

/* promenom koda ispod se odabira izmedju *
 * std::shared_ptr ili kotur::shared_ptr  */
using namespace kotur;
// using namespace std;

struct S {
    std::string m_str;
    std::string str() { return m_str; }
};

int main()
{
    auto sh1 = make_shared<S>(S{"Hello world"});

    {
        shared_ptr<S> sh2 = std::move(sh1);
        std::cout << sh2->str() << '\n';
        std::cout << sh2.use_count() << '\n';
    }

    std::cout << sh1.use_count() << '\n';

    return 0;
}
