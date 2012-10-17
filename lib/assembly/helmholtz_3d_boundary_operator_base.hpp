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

#ifndef bempp_helmholtz_3d_boundary_operator_base_hpp
#define bempp_helmholtz_3d_boundary_operator_base_hpp

#include "elementary_singular_integral_operator.hpp"

#include <boost/scoped_ptr.hpp>

namespace Bempp
{

const int DEFAULT_HELMHOLTZ_INTERPOLATION_DENSITY = 5000;

template <typename BasisFunctionType> class Helmholtz3dBoundaryOperatorId;

/** \ingroup helmholtz_3d
 *  \brief Base class for boundary operators for the Helmholtz equation in 3D.
 *
 *  \tparam Impl
 *    Type of the internal implementation object.
 *  \tparam BasisFunctionType
 *    Type of the values of the basis functions into which functions acted upon
 *    by the operator are expanded. It can take the following values: \c float,
 *    \c double, <tt>std::complex<float></tt> and
 *    <tt>std::complex<double></tt>.
 *
 *  \see helmholtz_3d
 */
template <typename Impl, typename BasisFunctionType_>
class Helmholtz3dBoundaryOperatorBase :
        public ElementarySingularIntegralOperator<
        BasisFunctionType_,
        typename ScalarTraits<BasisFunctionType_>::ComplexType,
        typename ScalarTraits<BasisFunctionType_>::ComplexType>
{
    typedef ElementarySingularIntegralOperator<
    BasisFunctionType_,
    typename ScalarTraits<BasisFunctionType_>::ComplexType,
    typename ScalarTraits<BasisFunctionType_>::ComplexType>
    Base;

    friend class Helmholtz3dBoundaryOperatorId<BasisFunctionType_>;

public:
    /** \brief Type of the values of the basis functions into which functions
     *  acted upon by the operator are expanded. */
    typedef typename Base::BasisFunctionType BasisFunctionType;
    /** \brief Type of the values of kernel functions. */
    typedef typename Base::KernelType KernelType;
    /** \copydoc ElementaryIntegralOperator::ResultType */
    typedef typename Base::ResultType ResultType;
    /** \copydoc ElementaryIntegralOperator::CoordinateType */
    typedef typename Base::CoordinateType CoordinateType;
    /** \copydoc ElementaryIntegralOperator::CollectionOfBasisTransformations */
    typedef typename Base::CollectionOfBasisTransformations
    CollectionOfBasisTransformations;
    /** \copydoc ElementaryIntegralOperator::CollectionOfKernels */
    typedef typename Base::CollectionOfKernels CollectionOfKernels;
    /** \copydoc ElementaryIntegralOperator::TestKernelTrialIntegral */
    typedef typename Base::TestKernelTrialIntegral TestKernelTrialIntegral;

    /** \brief Constructor.
     *
     *  \param[in] domain
     *    Function space being the domain of the operator.
     *  \param[in] range
     *    Function space being the range of the operator.
     *  \param[in] dualToRange
     *    Function space dual to the the range of the operator.
     *  \param[in] waveNumber
     *    Wave number. See \ref helmholtz_3d for its definition.
     *  \param[in] label
     *    Textual label of the operator. If empty, a unique label is generated
     *    automatically.
     *  \param[in] symmetry
     *    Symmetry of the weak form of the operator. Can be any combination of the
     *    flags defined in the enumeration type Symmetry.
     *  \param[in] useInterpolation
     *    If set to \p false (default), the exp() function from the standard C++
     *    library will be used to evaluate the exponential factor occurring in the
     *    kernel. If set to \p true, the exponential factor will be evaluated by
     *    piecewise-cubic interpolation of values calculated in advance on a
     *    regular grid. This normally speeds up calculations, but might result in a
     *    loss of accuracy. Use at your own risk.
     *  \param[in] interPtsPerWavelength
     *    If \p useInterpolation is set to true, this parameter determines the
     *    number of points per "effective wavelength" (defined as \f$2\pi/|k|\f$,
     *    where \f$k\f$ = \p waveNumber) used to construct the interpolation grid.
     *    The default value (5000) should ensure that the interpolated values are
     *    accurate to about 50 * machine precision.
     *
     *  None of the shared pointers may be null and the spaces \p range and \p
     *  dualToRange must be defined on the same grid, otherwise an exception is
     *  thrown. */
    Helmholtz3dBoundaryOperatorBase(
            const shared_ptr<const Space<BasisFunctionType> >& domain,
            const shared_ptr<const Space<BasisFunctionType> >& range,
            const shared_ptr<const Space<BasisFunctionType> >& dualToRange,
            KernelType waveNumber,
            const std::string& label = "",
            int symmetry = NO_SYMMETRY,
            bool useInterpolation = false,
            int interpPtsPerWavelength = DEFAULT_HELMHOLTZ_INTERPOLATION_DENSITY);

    /** \brief Copy constructor. */
    Helmholtz3dBoundaryOperatorBase(
            const Helmholtz3dBoundaryOperatorBase& other);

    /** \brief Destructor. */
    virtual ~Helmholtz3dBoundaryOperatorBase();

    /** \brief Return the wave number set previously in the constructor. */
    KernelType waveNumber() const;

    /** \brief Return the identifier of this operator.
     *
     *  Two boundary operators related to the Helmholtz equation are treated as
     *  identical, and hence having the same weak form, if they have the same
     *  C++ type (e.g.
     *  <tt>Helmholtz3dDoubleLayerBoundaryOperator<double></tt>), domain space,
     *  range space, space dual to range and wave number. */
    virtual shared_ptr<const AbstractBoundaryOperatorId> id() const;

private:
    virtual const CollectionOfKernels& kernels() const;
    virtual const CollectionOfBasisTransformations&
    testTransformations() const;
    virtual const CollectionOfBasisTransformations&
    trialTransformations() const;
    virtual const TestKernelTrialIntegral& integral() const;

private:
    /** \cond PRIVATE */
    boost::scoped_ptr<Impl> m_impl;
    shared_ptr<AbstractBoundaryOperatorId> m_id;
    /** \endcond */
};

} // namespace Bempp

#endif
