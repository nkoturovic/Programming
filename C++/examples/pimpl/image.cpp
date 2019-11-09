#include "image.hpp"
#include "image_impl.hpp"

namespace rs {

Image::Image(std::string_view image_path) : m_pimpl{new ImageImpl(image_path)} {}
Image::~Image() = default;

Image::ImageImpl& Image::pimpl() {
    return *m_pimpl;
}

void Image::show() const {
    m_pimpl->show();
}

} // namespace rs
