#include "image_impl.hpp"

namespace rs {

Image::ImageImpl::ImageImpl(std::string_view image_path) : m_image(cv::imread(cv::String(image_path))) {}

} // namespace rs
