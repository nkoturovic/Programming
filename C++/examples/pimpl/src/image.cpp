#include "../include/image.hpp"
#include "../include/implementation/image_impl.hpp"

using namespace rs::interface;

namespace rs {

Image::Image(std::string_view image_path) : m_pimpl{new ImageImpl(image_path)} { }

void Image::show() const {
    m_pimpl->show();
}

void Image::applyTransfromation(const Transformation &t) {
    m_pimpl->applyTransfromation(std::forward<const Transformation &>(t));
}


} // namespace rs
