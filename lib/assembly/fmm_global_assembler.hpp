// Copyright (C) 2011-2012 by the BEM++ Authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef bempp_fmm_global_assembler_hpp
#define bempp_fmm_global_assembler_hpp

#include "../common/common.hpp"

#include "../common/shared_ptr.hpp"
#include "../fiber/scalar_traits.hpp"
#include "../common/eigen_support.hpp"
#include "../common/types.hpp"
#include "../fmm/fmm_transform.hpp"

#include "elementary_integral_operator.hpp"

#include <memory>
#include <vector>

namespace Fiber {

/** \cond FORWARD_DECL */
template <typename ResultType> class LocalAssemblerForIntegralOperators;
template <typename ResultType> class LocalAssemblerForPotentialOperators;
/** \endcond */

} // namespace Fiber

namespace Bempp {

/** \cond FORWARD_DECL */
class AssemblyOptions;
class EvaluationOptions;
template <typename ValueType> class DiscreteBoundaryOperator;
template <typename BasisFunctionType> class Space;
template <typename BasisFunctionType, typename ResultType> class Context;
/** \endcond */

/** \ingroup weak_form_assembly_internal
 *  \brief FMM-mode assembler.
 */
template <typename BasisFunctionType, typename ResultType>
class FMMGlobalAssembler {
  typedef typename Fiber::ScalarTraits<ResultType>::RealType CoordinateType;

public:
  typedef DiscreteBoundaryOperator<ResultType> DiscreteBndOp;
  typedef Fiber::LocalAssemblerForIntegralOperators<ResultType>
      LocalAssemblerForIntegralOperators;
  typedef LocalAssemblerForIntegralOperators
      LocalAssemblerForBoundaryOperators;                    // deprecated
  typedef LocalAssemblerForBoundaryOperators LocalAssembler; // deprecated
  typedef Fiber::LocalAssemblerForPotentialOperators<ResultType>
      LocalAssemblerForPotentialOperators;

  static std::unique_ptr<DiscreteBndOp> assembleDetachedWeakForm(
      const Space<BasisFunctionType> &testSpace,
      const Space<BasisFunctionType> &trialSpace,
      //const LocalAssembler &assembler,
      const std::vector<LocalAssembler*> &localAssemblers,
      const std::vector<const DiscreteBndOp*>& sparseTermsToAdd,
      const std::vector<ResultType>& denseTermsMultipliers,
      const std::vector<ResultType>& sparseTermsMultipliers,
      const Context<BasisFunctionType, ResultType> &context,
      const fmm::FmmTransform<ResultType>& fmmTransform,
      int symmetry);

  static std::unique_ptr<DiscreteBndOp> assembleDetachedWeakForm(
        const Space<BasisFunctionType>& testSpace,
        const Space<BasisFunctionType>& trialSpace,
        LocalAssembler& localAssembler,
        const Context<BasisFunctionType, ResultType>& context,
        const fmm::FmmTransform<ResultType>& fmmTransform,
        int symmetry);

  static void getDofPositionsAndCorners(
    const Space<BasisFunctionType>& space,
    const size_t dofCount,
    std::vector<Point3D<CoordinateType>> &locations,
    std::vector<std::vector<Point3D<CoordinateType>>> &corners);




  static std::unique_ptr<DiscreteBndOp> assemblePotentialOperator(
      const Matrix<CoordinateType> &points,
      const Space<BasisFunctionType> &trialSpace,
      const std::vector<LocalAssemblerForPotentialOperators *> &localAssemblers,
      const std::vector<ResultType> &termMultipliers,
      const EvaluationOptions &options);

  static std::unique_ptr<DiscreteBndOp>
  assemblePotentialOperator(const Matrix<CoordinateType> &points,
                            const Space<BasisFunctionType> &trialSpace,
                            LocalAssemblerForPotentialOperators &localAssembler,
                            const ParameterList &parameterList);
};

} // namespace Bempp

#endif