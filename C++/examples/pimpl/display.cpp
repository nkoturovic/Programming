#include "display.hpp"
#include "image_impl.hpp"

namespace rs {

Display::Display(std::string_view name_of_display) : m_display_name(name_of_display) {
    static unsigned displayCounter = 0;
    m_display_id = displayCounter++;
}

void Display::show(Image &img) {
    cv::imshow(std::to_string(m_display_id) + ":" + m_display_name, img.pimpl().m_image);
}

void Display::waitKey(int delay) {
    cv::waitKey(delay);
}

}

