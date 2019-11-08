#ifndef RS_TRANSFORMATIONS_IMPL_H
#define RS_TRANSFORMATIONS_IMPL_H

#include "../transformations.hpp"

namespace rs::transformations {

class RotationImpl : public transformations::Rotation::RotationImplBase {
public:
    RotationImpl(double degrees);
    virtual void operator()(interface::Transformable &t) const override;
    virtual std::unique_ptr<RotationImplBase> clone() const override; 
private:
    double m_degrees;
};

} // namespace rs

#endif // RS_TRANSFORMATIONS_H
