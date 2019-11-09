#ifndef RS_IMAGE_IMPL_H
#define RS_IMAGE_IMPL_H

#include "image.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

struct Image::ImageImpl {
    ImageImpl(std::string_view image_path);
    cv::Mat m_image;
    void show() const;
};

} // namespace rs

#endif // RS_IMAGE_IMPL_H
