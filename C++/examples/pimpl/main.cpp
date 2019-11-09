#include "image.hpp"
#include "transform.hpp"

int main()
{
    rs::Image img("/home/kotur/Pictures/lee.jpg");
    img.show();

    auto comp = rs::Rotate(10) * rs::Rotate(12);
    img << rs::Rotate(30) * comp;

    img.show();

    return 0;
}
