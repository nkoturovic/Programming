#include <iostream>
#include "image.hpp"

int main()
{
    rs::Image img("/home/kotur/Pictures/lee.jpg");
    rs::Image img2 = std::move(img);

    img2.rotate(90);
    img2.show();
}
