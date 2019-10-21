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
    auto sh0 = shared_ptr<S>(nullptr);
    auto sh1 = make_shared<S>(S{"Hello world"});

    {
        shared_ptr<S> sh2 = std::move(sh1);
        shared_ptr<S> sh3 = sh2;
        std::cout << sh3->str() << '\n';
        std::cout << sh3.use_count() << '\n';
        sh0.swap(sh3);
    }

    shared_ptr<S> tmp(nullptr);
    sh1.swap(tmp);
    std::cout << sh0->str() << std::endl;

    std::cout << sh1.use_count() << '\n';

    return 0;
}
