#include "../../include/implementation/transformations_impl.hpp"
#include "../../include/implementation/image_impl.hpp"

using namespace rs::interface;

namespace rs::transformations {

RotationImpl::RotationImpl(double degrees) : m_degrees(degrees) { }

void RotationImpl::operator()(Transformable &t) const {
   ImageImpl& imgImpl = static_cast<ImageImpl&>(t);
   img_type &image = imgImpl.m_image;

  // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((image.cols-1)/2.0, (image.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, m_degrees, 1.0);
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), image.size(), m_degrees).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - image.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - image.rows/2.0;

    cv::warpAffine(image, image, rot, bbox.size());
}

std::unique_ptr<Rotation::RotationImplBase> RotationImpl::clone() const {
    return std::unique_ptr<RotationImpl>(new RotationImpl(*this));
}

} // namespace rs
