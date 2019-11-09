#include "transform.hpp"
#include "image_impl.hpp"

namespace rs {

Rotate::Rotate(double degrees) : m_degrees(degrees) {}

Image& Rotate::applyToImpl(Image &img) const {
    cv::Mat &image = img.pimpl().m_image;

    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((image.cols-1)/2.0, (image.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, m_degrees, 1.0);

    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), image.size(), m_degrees).boundingRect2f();

    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - image.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - image.rows/2.0;

    cv::warpAffine(image, image, rot, bbox.size());
    return img;
}

Composition::Composition(const Transform& tr1, const Transform& tr2) : 
    m_composition( [&tr1, &tr2](Image &img) -> Image& { return (img <<= tr2) <<= tr1; } ) {}

Image& Composition::applyToImpl(Image &img) const {
    return m_composition(img);
}


} // namespace rs
