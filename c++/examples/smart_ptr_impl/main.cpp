#include <iostream>
#include <memory>
#include <cassert>
#include "shared_ptr.hpp"
#include "unique_ptr.hpp"

/* promenom koda ispod se odabira izmedju *
 * std::shared_ptr ili kotur::shared_ptr, i  
 * std::unique_ptr ili kotur::unique_ptr  */
using namespace kotur;
// using namespace std;

struct S {
    std::string m_str;
    std::string str() { return m_str; }
};

int main()
{
    /******** shared_ptr ********/
    auto sh0 = shared_ptr<S>(nullptr);
    std::cout << sh0.use_count() << '\n';

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
    std::cout << sh0->str() << '\n';

    std::cout << sh1.use_count() << '\n';

    /******** unique_ptr ********/
    auto un0 = unique_ptr<S>(nullptr);

    auto un1 = make_unique<S>(S{"Hello world"});

    {
        unique_ptr<S> un2 = std::move(un1);
        assert(un1.get() == nullptr);
        assert(un2.get() != nullptr);

        unique_ptr<S> un3 = std::move(un2);
        assert(un2.get() == nullptr);
        assert(un3.get() != nullptr);

        std::cout << un3->str() << '\n';
        un0.swap(un3);
    }

    unique_ptr<S> utmp(nullptr);
    un1.swap(utmp);
    std::cout << un0->str() << '\n';

    return 0;
}
