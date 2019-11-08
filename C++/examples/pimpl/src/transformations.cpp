#include "../include/transformations.hpp"
#include "../include/implementation/transformations_impl.hpp"

using namespace rs::interface;

namespace rs::transformations {

Rotation::Rotation(double degrees) : m_pimpl { new RotationImpl(degrees)} { }

void Rotation::operator()(Transformable &t) const {
    m_pimpl->operator()(t);
}

} // namespace rs
