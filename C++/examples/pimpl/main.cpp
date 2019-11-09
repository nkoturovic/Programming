#include "image.hpp"
#include "transform.hpp"
#include "display.hpp"

int main()
{
    rs::Image img("/home/kotur/Pictures/lee.jpg");
    img <<= rs::Rotate(30) * rs::Rotate(60);
    rs::Image img2 = img << rs::Rotate(30) * rs::Rotate(13);

    rs::Display disp1;
    disp1.show(img);

    rs::Display disp2;
    disp2.show(img2);

    rs::Display::waitKey();

    return 0;
}
