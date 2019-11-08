#ifndef RS_TRANSFORMATIONS_H
#define RS_TRANSFORMATIONS_H

#include "interface/transform.hpp"
#include "utility/pimpl.hpp"

namespace rs::transformations {

class Rotation : public interface::Transformation {
    friend class RotationImpl;
public:
    Rotation(double degrees);
    virtual void operator()(interface::Transformable &t) const override;
private:
    struct RotationImplBase;
    utility::pimpl<RotationImplBase> m_pimpl;
};

struct Rotation::RotationImplBase : public Transformation {
    virtual void operator()(interface::Transformable &t) const = 0;
    virtual ~RotationImplBase() = default;
    virtual std::unique_ptr<RotationImplBase> clone() const = 0;
};

} // namespace rs

#endif
