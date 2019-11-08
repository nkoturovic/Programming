#ifndef RS_IMAGE_PIMPL_H
#define RS_IMAGE_PIMPL_H

#include "image.hpp"
#include <opencv2/opencv.hpp>

namespace rs {

class ImageImpl : public Image::ImageImplBase {
    using img_type = cv::Mat;
public:
    ImageImpl(std::string_view path);

    virtual void show() const override;
    virtual void rotate(double degrees) override;
    virtual void adjustBrightness(double amount) override;

    virtual std::unique_ptr<ImageImplBase> clone() const override; 
private:
    img_type m_image;
};

} // namespace rs

#endif  // RS_IMAGE_PIMPL_H
