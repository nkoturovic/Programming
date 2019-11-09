#ifndef RS_IMAGE_H
#define RS_IMAGE_H

#include <string_view>
#include "pimpl.hpp"

namespace rs {

class Image {
private:
    struct ImageImpl;
    rs::utility::pimpl<ImageImpl> m_pimpl; 

public:
    Image(std::string_view image_path);
    ~Image();
    
    ImageImpl& pimpl();
    void show() const;
};

}

#endif // RS_IMAGE_H
