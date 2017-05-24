#ifndef bempp_fmm_farfield_function_multiplying_hpp
#define bempp_fmm_farfield_function_multiplying_hpp

#include "fmm_common.hpp"
#include "../common/scalar_traits.hpp"

namespace fmm
{

/** \cond FORWARD_DECL */
template <typename ResultType> class FmmTransform;
/** \endcond */

template <typename ResultType>
class FmmFarfieldFunctionMultiplying
{
public:
  typedef ResultType ValueType;
  typedef typename Bempp::ScalarTraits<ValueType>::RealType CoordinateType;

  FmmFarfieldFunctionMultiplying(const Vector<CoordinateType>& khat,
      const Vector<CoordinateType>& nodeCentre,
      const Vector<CoordinateType>& nodeSize,
      const FmmTransform<ResultType>& fmmTransform,
      const bool isTest);

  // Number of components of the function's argument
  int argumentDimension() const;
  // Number of components of the function's value
  int resultDimension() const;

  // Evaluate the function at the point "point" and store result in
  // the array "result"
  void evaluate(const Vector<CoordinateType>& point,
      const Vector<CoordinateType>& normal,
      Vector<ValueType>& result) const;
private:
  const Vector<CoordinateType> &m_khat;
  const Vector<CoordinateType> &m_nodeCentre;
  const Vector<CoordinateType> &m_nodeSize;
  const FmmTransform<ResultType>& m_fmmTransform;
  const bool m_isTest;
};

} // namespace Bempp

#endif