#ifndef FMM_COMMON_HPP
#define FMM_COMMON_HPP

#include "../common/types.hpp"
#include "../common/shared_ptr.hpp"

namespace fmm {

template <typename T> using Vector = Bempp::Vector<T>;
template <typename T> using Matrix = Bempp::Matrix<T>;
template <typename T> using Point3D = Bempp::Point3D<T>;

template <typename T>
Vector<T> Point2Vector(Point3D<T> p){
  Vector<T> result;
  result.resize(3);
  result(0) = p.x;
  result(1) = p.y;
  result(2) = p.z;
  return result;
}

using Bempp::shared_ptr;
using Bempp::make_shared_from_ref;
using Bempp::make_shared_from_const_ref;
using Bempp::null_deleter;
using Bempp::dynamic_pointer_cast;
using Bempp::static_pointer_cast;
using Bempp::const_pointer_cast;

template <typename T>
void nice_print(Vector<T> v){
  for(size_t i=0;i<v.rows();++i)
    std::cout << v(i) << " ";
}
template <typename T>
void nice_print(std::vector<T> v){
  for(size_t i=0;i<v.size();++i)
    std::cout << v[i] << " ";
}
template <typename T>
void nice_print(Matrix<T> v){
  for(size_t i=0;i<v.rows();++i){
    for(size_t j=0;j<v.cols();++j)
      std::cout << v(i,j) << " ";
    if(i<v.rows()-1) std::cout << ", ";
  }
}

}

#endif
