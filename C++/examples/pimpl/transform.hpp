#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include "image.hpp"
#include <functional>
#include <vector>

namespace rs {

class Transform {
public:
    friend Image& operator<<=(Image &img, const Transform& tr) { 
        return tr.applyToImpl(img); 
    }

    friend Image operator<<(const Image &img, const Transform& tr) { 
        Image copy(img);
        return copy <<= tr;
    }

private:
    virtual Image& applyToImpl(Image &) const = 0;
};

class Composition : public Transform {
public:
    friend Composition operator*(const Transform& tr1, const Transform& tr2) 
    { return Composition(tr1, tr2); }

private:
    Composition(const Transform& tr1, const Transform& tr2);

    virtual Image& applyToImpl(Image &) const override;
    std::function<Image&(Image&)> m_composition;
};

class Rotate : public Transform {
public:
    Rotate(double degrees);
private:
    virtual Image& applyToImpl(Image &) const override;
    double m_degrees;
};

Image& operator<<=(Image &img, const Transform& tr);
Image operator<<(const Image &img, const Transform& tr);
Composition operator*(const Transform& tr1, const Transform& tr2);

} // namespace rs

#endif
