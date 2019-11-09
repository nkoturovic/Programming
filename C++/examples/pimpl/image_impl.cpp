#include "image_impl.hpp"

namespace rs {

Image::ImageImpl::ImageImpl(std::string_view image_path) : m_image(cv::imread(cv::String(image_path))) {}

void Image::ImageImpl::show() const {
    cv::imshow("win", m_image); 
    cv::waitKey();
}

} // namespace rs
