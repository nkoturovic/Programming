#ifndef RS_IMAGE_H
#define RS_IMAGE_H

/* For implementation of this class 'PIMPL' idiom is used 
 * with some modification, for implementator to be able to 
 * inherit from pimpl base class and have multiple pImpl-s */

/* https://herbsutter.com/gotw/_100/
 * put all private nonvirtual members into impl;
 * Option 4 (Score: 10 / 10): This is the ideal. To reduce the need 
 * for storing or passing a back pointer, you may also put into the 
 * Pimpl any public functions that the private functions call, with 
 * passthroughs to them in the visible class. However, you won’t be 
 * able to move the protected or virtual functions into the Pimpl,
 * as noted above. */

#include <string_view>
#include "utility/pimpl.hpp"
#include "interface/transform.hpp"

namespace rs {

class Image : public interface::Transformable {
    /* impl class name must be ImageImpl */
    friend class ImageImpl;
public:
    Image(std::string_view image_path);
    void show() const;

    virtual void applyTransfromation(const interface::Transformation &t) override;
private:
    struct ImageImplBase;
    utility::pimpl<Image::ImageImplBase> m_pimpl;
};

struct Image::ImageImplBase : public interface::Transformable {
    ImageImplBase(std::string_view) { };
    virtual ~ImageImplBase() = default;
    virtual void show() const = 0;

    virtual void applyTransfromation(const interface::Transformation &t) = 0;
    virtual std::unique_ptr<ImageImplBase> clone() const = 0;
};

} // namespace rs

#endif // RS_IMAGE_H
