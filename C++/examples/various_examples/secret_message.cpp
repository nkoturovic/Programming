#include <iostream>
#include <algorithm>

char changeCase(char c) { 
    if (isupper(c))
        return tolower(c);
    else if (islower(c))
        return toupper(c);
    else 
        return c;
}

std::string encode(const std::string msg) {
    std::string retval;
    retval.resize(msg.length());
    std::transform(msg.crbegin(), 
                   msg.crend(), 
                   retval.begin(), 
                   [](char c) -> char {
                        return changeCase(c) + 1;
                    }
    ); 
    return retval;
}

std::string decode(const std::string msg) {
    std::string retval;
    retval.resize(msg.length());
    std::transform(msg.crbegin(), 
                   msg.crend(), 
                   retval.begin(), 
                   [](char c) -> char {
                        return changeCase(c) - 1;
                    }
    ); 
    return retval;
}

int main()
{
    std::string msg;
    std::getline(std::cin, msg);

    auto e = encode(msg);
    auto d = decode(e);

    std::cout << "Coded message: " << e << '\n';
    std::cout << "Decoded message: " << d << '\n';

    return 0;
}
