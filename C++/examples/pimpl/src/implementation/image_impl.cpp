#include "../../include/implementation/image_impl.hpp"
#include <opencv2/opencv.hpp>

using namespace rs::interface;

namespace rs {

ImageImpl::ImageImpl(std::string_view path) : ImageImplBase(path), m_image(cv::imread(cv::String(path))) {}

void ImageImpl::show() const {
    std::string win_name("win");
    cv::namedWindow(win_name);
    cv::imshow(win_name, m_image);
    cv::waitKey();
}

void ImageImpl::applyTransfromation(const Transformation &t) {
   t(*this); 
}

std::unique_ptr<Image::ImageImplBase> ImageImpl::clone() const {
    return std::unique_ptr<ImageImplBase>(new ImageImpl(*this));
}

} // namespace rs
