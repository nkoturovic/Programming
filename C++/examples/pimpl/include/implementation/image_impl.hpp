#ifndef RS_IMAGE_PIMPL_H
#define RS_IMAGE_PIMPL_H

#include "../image.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

using img_type = cv::Mat;

class ImageImpl : public Image::ImageImplBase {
public:
    ImageImpl(std::string_view path);
    virtual void show() const override;

    virtual void applyTransfromation(const interface::Transformation &t) override;
    virtual std::unique_ptr<ImageImplBase> clone() const override; 
    img_type m_image;
};

} // namespace rs

#endif  // RS_IMAGE_PIMPL_H
