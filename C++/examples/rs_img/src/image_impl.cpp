#include "../include/rsimg/implementation/image_impl.hpp"
#include "../include/rsimg/exception.hpp"

namespace rs {

Image::ImageImpl& get_impl(Image &img) {
    return img.impl();
}

Image::ImageImpl::ImageImpl(std::string &&image_path) : m_image(cv::imread(image_path)) {
     if (m_image.empty()) 
         throw rs::Exception("Image not exists: " + image_path);
}

void Image::ImageImpl::ImageImpl::write(std::string image_path) {
    cv::imwrite(image_path, m_image);
}

} // namespace rs
