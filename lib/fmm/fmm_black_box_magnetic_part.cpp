#include "fmm_black_box_magnetic_part.hpp"
#include "fmm_black_box.hpp"
#include "fmm_transform.hpp"

#include "../fiber/explicit_instantiation.hpp"

namespace fmm
{

template <typename KernelType, typename ValueType>
void FmmBlackBoxMagneticPart<KernelType, ValueType>::evaluateTrial(
    const Vector<CoordinateType>& point,
    const Vector<CoordinateType>& normal,
    const Vector<CoordinateType>& multipole,
    const Vector<CoordinateType>& nodeCentre,
    const Vector<CoordinateType>& nodeSize,
    Vector<ValueType>& result) const
{
  this->evaluateAtGaussPointS(point, normal, multipole,
      nodeCentre, nodeSize, result);
}

template <typename KernelType, typename ValueType>
void FmmBlackBoxMagneticPart<KernelType, ValueType>::evaluateTest(
    const Vector<CoordinateType>& point,
    const Vector<CoordinateType>& normal,
    const Vector<CoordinateType>& multipole,
    const Vector<CoordinateType>& nodeCentre,
    const Vector<CoordinateType>& nodeSize,
    Vector<ValueType>& result) const
{
  this->evaluateAtGaussPointGradSComponent(point, normal, multipole,
      nodeCentre, nodeSize, m_component, result);
}

FIBER_INSTANTIATE_CLASS_TEMPLATED_ON_BASIS_AND_RESULT(FmmBlackBoxMagneticPart);

} // namespace Bempp
