#include <iostream>
#include "image.hpp"
#include "transformations.hpp"

int main()
{
    rs::Image img("/home/kotur/Pictures/lee.jpg");
    img.applyTransfromation(rs::transformations::Rotation(90));
    rs::Image img2 = std::move(img);
    img2.show();
}
