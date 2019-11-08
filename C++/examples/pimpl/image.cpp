#include "image.hpp"
#include "image_impl.hpp"

namespace rs {

Image::Image(std::string_view image_path) : m_pimpl{new ImageImpl(image_path)} { }

void Image::rotate(double degrees) {
    m_pimpl->rotate(std::forward<double>(degrees));
}

void Image::adjustBrightness(double amount) {
    m_pimpl->adjustBrightness(std::forward<double>(amount));
}

void Image::show() const {
    m_pimpl->show();
}

} // namespace rs
