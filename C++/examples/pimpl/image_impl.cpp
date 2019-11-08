#include "image_impl.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

ImageImpl::ImageImpl(std::string_view path) : ImageImplBase(path), m_image(cv::imread(cv::String(path))) {}

void ImageImpl::rotate(double degrees) {
  // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((m_image.cols-1)/2.0, (m_image.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, degrees, 1.0);
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), m_image.size(), degrees).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - m_image.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - m_image.rows/2.0;

    cv::warpAffine(m_image, m_image, rot, bbox.size());
}

void ImageImpl::show() const {
    std::string win_name("win");
    cv::namedWindow(win_name);
    cv::imshow(win_name, m_image);
    cv::waitKey();
}

void ImageImpl::adjustBrightness(double) {
    // TODO
}

std::unique_ptr<Image::ImageImplBase> ImageImpl::clone() const {
    return std::unique_ptr<ImageImplBase>(new ImageImpl(*this));
}

} // namespace rs
