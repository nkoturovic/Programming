#include <cctype>
#include <cmath>
#include <string>
#include "composition.hpp"

auto sifruj(char c) {

    auto comp = rs::transform(toupper) 
              | rs::transform(toascii)
              | rs::transform([](auto x) -> int { return pow(x,3); })
              | rs::transform([](auto x) { 
                      if (x % 2 == 0) {
                        return std::string("Paran");
                      } else {
                        return std::string("NeParan");
                      }
              })
              ;

    return comp(c); 
}
