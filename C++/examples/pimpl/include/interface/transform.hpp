#ifndef RS_TRANSFORM_H
#define RS_TRANSFORM_H

#include <utility>
#include "../utility/pimpl.hpp"

namespace rs::interface {

class Transformation;

class Transformable {
public:
    virtual void applyTransfromation(const Transformation &t) = 0;
};


class Transformation { 
public:
    virtual void operator()(Transformable &t) const = 0;
};


} // namespace rs::interface

#endif
