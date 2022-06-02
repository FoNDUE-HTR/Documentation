#include <pythonic/core.hpp>
#include <pythonic/python/core.hpp>
#include <pythonic/types/bool.hpp>
#include <pythonic/types/int.hpp>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <pythonic/include/types/float64.hpp>
#include <pythonic/include/types/ndarray.hpp>
#include <pythonic/include/types/float.hpp>
#include <pythonic/include/types/int.hpp>
#include <pythonic/include/types/numpy_texpr.hpp>
#include <pythonic/types/ndarray.hpp>
#include <pythonic/types/numpy_texpr.hpp>
#include <pythonic/types/float.hpp>
#include <pythonic/types/float64.hpp>
#include <pythonic/types/int.hpp>
#include <pythonic/include/builtins/assert.hpp>
#include <pythonic/include/builtins/getattr.hpp>
#include <pythonic/include/builtins/int_.hpp>
#include <pythonic/include/builtins/max.hpp>
#include <pythonic/include/builtins/range.hpp>
#include <pythonic/include/builtins/tuple.hpp>
#include <pythonic/include/numpy/double_.hpp>
#include <pythonic/include/numpy/empty_like.hpp>
#include <pythonic/include/numpy/square.hpp>
#include <pythonic/include/operator_/add.hpp>
#include <pythonic/include/operator_/div.hpp>
#include <pythonic/include/operator_/eq.hpp>
#include <pythonic/include/operator_/floordiv.hpp>
#include <pythonic/include/operator_/gt.hpp>
#include <pythonic/include/operator_/iadd.hpp>
#include <pythonic/include/operator_/le.hpp>
#include <pythonic/include/operator_/lt.hpp>
#include <pythonic/include/operator_/mod.hpp>
#include <pythonic/include/operator_/mul.hpp>
#include <pythonic/include/operator_/neg.hpp>
#include <pythonic/include/operator_/sub.hpp>
#include <pythonic/include/types/str.hpp>
#include <pythonic/builtins/assert.hpp>
#include <pythonic/builtins/getattr.hpp>
#include <pythonic/builtins/int_.hpp>
#include <pythonic/builtins/max.hpp>
#include <pythonic/builtins/range.hpp>
#include <pythonic/builtins/tuple.hpp>
#include <pythonic/numpy/double_.hpp>
#include <pythonic/numpy/empty_like.hpp>
#include <pythonic/numpy/square.hpp>
#include <pythonic/operator_/add.hpp>
#include <pythonic/operator_/div.hpp>
#include <pythonic/operator_/eq.hpp>
#include <pythonic/operator_/floordiv.hpp>
#include <pythonic/operator_/gt.hpp>
#include <pythonic/operator_/iadd.hpp>
#include <pythonic/operator_/le.hpp>
#include <pythonic/operator_/lt.hpp>
#include <pythonic/operator_/mod.hpp>
#include <pythonic/operator_/mul.hpp>
#include <pythonic/operator_/neg.hpp>
#include <pythonic/operator_/sub.hpp>
#include <pythonic/types/str.hpp>
namespace __pythran__hessian_det_appx
{
  struct _clip
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 , typename argument_type1 , typename argument_type2 >
    struct type
    {
      typedef typename std::remove_cv<typename std::remove_reference<argument_type2>::type>::type __type0;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type1;
      typedef typename __combined<__type0,__type1>::type __type2;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type3;
      typedef typename pythonic::returnable<typename __combined<__type2,__type3>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 , typename argument_type1 , typename argument_type2 >
    inline
    typename type<argument_type0, argument_type1, argument_type2>::result_type operator()(argument_type0&& x, argument_type1&& low, argument_type2&& high) const
    ;
  }  ;
  struct _integ
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 , typename argument_type1 , typename argument_type2 , typename argument_type3 , typename argument_type4 >
    struct type
    {
      typedef _clip __type0;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type1;
      typedef long __type2;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type3;
      typedef decltype(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, std::declval<__type3>())) __type4;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type4>::type>::type __type5;
      typedef decltype(pythonic::operator_::sub(std::declval<__type5>(), std::declval<__type2>())) __type6;
      typedef decltype(std::declval<__type0>()(std::declval<__type1>(), std::declval<__type2>(), std::declval<__type6>())) __type7;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type2>::type>::type __type8;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type4>::type>::type __type11;
      typedef decltype(pythonic::operator_::sub(std::declval<__type11>(), std::declval<__type2>())) __type12;
      typedef decltype(std::declval<__type0>()(std::declval<__type8>(), std::declval<__type2>(), std::declval<__type12>())) __type13;
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::builtins::functor::max{})>::type>::type __type14;
      typedef double __type15;
      typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type1>(), std::declval<__type2>(), std::declval<__type6>()))>::type __type17;
      typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type8>(), std::declval<__type2>(), std::declval<__type12>()))>::type __type18;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type17>(), std::declval<__type18>())) __type19;
      typedef decltype(std::declval<__type3>()[std::declval<__type19>()]) __type20;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type3>::type>::type __type23;
      typedef decltype(pythonic::operator_::add(std::declval<__type17>(), std::declval<__type23>())) __type24;
      typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type24>(), std::declval<__type2>(), std::declval<__type6>()))>::type __type29;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type4>::type>::type __type31;
      typedef decltype(pythonic::operator_::add(std::declval<__type18>(), std::declval<__type31>())) __type32;
      typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type32>(), std::declval<__type2>(), std::declval<__type12>()))>::type __type37;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type29>(), std::declval<__type37>())) __type38;
      typedef decltype(std::declval<__type3>()[std::declval<__type38>()]) __type39;
      typedef decltype(pythonic::operator_::add(std::declval<__type20>(), std::declval<__type39>())) __type40;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type17>(), std::declval<__type37>())) __type44;
      typedef decltype(std::declval<__type3>()[std::declval<__type44>()]) __type45;
      typedef decltype(pythonic::operator_::sub(std::declval<__type40>(), std::declval<__type45>())) __type46;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type29>(), std::declval<__type18>())) __type50;
      typedef decltype(std::declval<__type3>()[std::declval<__type50>()]) __type51;
      typedef decltype(pythonic::operator_::sub(std::declval<__type46>(), std::declval<__type51>())) __type52;
      typedef typename __combined<__type15,__type52>::type __type53;
      typedef __type7 __ptype0;
      typedef __type13 __ptype1;
      typedef typename pythonic::returnable<decltype(std::declval<__type14>()(std::declval<__type53>(), std::declval<__type52>()))>::type result_type;
    }  
    ;
    template <typename argument_type0 , typename argument_type1 , typename argument_type2 , typename argument_type3 , typename argument_type4 >
    inline
    typename type<argument_type0, argument_type1, argument_type2, argument_type3, argument_type4>::result_type operator()(argument_type0&& img, argument_type1&& r, argument_type2&& c, argument_type3&& rl, argument_type4&& cl) const
    ;
  }  ;
  struct _hessian_matrix_det
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 , typename argument_type1 >
    struct type
    {
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty_like{})>::type>::type __type0;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type1;
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::double_{})>::type>::type __type2;
      typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type1>(), std::declval<__type2>()))>::type __type3;
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::builtins::functor::range{})>::type>::type __type4;
      typedef decltype(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, std::declval<__type1>())) __type6;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type6>::type>::type __type7;
      typedef typename pythonic::lazy<__type7>::type __type8;
      typedef decltype(std::declval<__type4>()(std::declval<__type8>())) __type9;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type9>::type::iterator>::value_type>::type __type10;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type6>::type>::type __type11;
      typedef typename pythonic::lazy<__type11>::type __type12;
      typedef decltype(std::declval<__type4>()(std::declval<__type12>())) __type13;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type13>::type::iterator>::value_type>::type __type14;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type10>(), std::declval<__type14>())) __type15;
      typedef indexable<__type15> __type16;
      typedef typename __combined<__type3,__type16>::type __type17;
      typedef _integ __type18;
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::builtins::functor::int_{})>::type>::type __type21;
      typedef long __type22;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type23;
      typedef decltype(pythonic::operator_::mul(std::declval<__type22>(), std::declval<__type23>())) __type24;
      typedef typename pythonic::assignable<decltype(std::declval<__type21>()(std::declval<__type24>()))>::type __type25;
      typedef typename pythonic::assignable<decltype(pythonic::operator_::functor::floordiv()(std::declval<__type25>(), std::declval<__type22>()))>::type __type26;
      typedef decltype(pythonic::operator_::sub(std::declval<__type10>(), std::declval<__type26>())) __type27;
      typedef decltype(pythonic::operator_::add(std::declval<__type27>(), std::declval<__type22>())) __type28;
      typedef decltype(pythonic::operator_::sub(std::declval<__type25>(), std::declval<__type22>())) __type31;
      typedef typename pythonic::assignable<decltype(pythonic::operator_::functor::floordiv()(std::declval<__type31>(), std::declval<__type22>()))>::type __type32;
      typedef decltype(pythonic::operator_::sub(std::declval<__type14>(), std::declval<__type32>())) __type33;
      typedef decltype(pythonic::operator_::mul(std::declval<__type22>(), std::declval<__type26>())) __type35;
      typedef decltype(pythonic::operator_::sub(std::declval<__type35>(), std::declval<__type22>())) __type36;
      typedef typename pythonic::assignable<typename pythonic::assignable<decltype(std::declval<__type21>()(std::declval<__type24>()))>::type>::type __type37;
      typedef decltype(pythonic::operator_::add(std::declval<__type37>(), std::declval<__type22>())) __type38;
      typedef typename __combined<__type37,__type38>::type __type39;
      typedef typename _integ::type<__type1, __type28, __type33, __type36, __type39>::__ptype0 __type40;
      typedef typename __combined<__type28,__type40>::type __type41;
      typedef typename _integ::type<__type1, __type41, __type33, __type36, __type39>::__ptype1 __type42;
      typedef typename __combined<__type33,__type42>::type __type43;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type41>(), std::declval<__type43>(), std::declval<__type36>(), std::declval<__type39>())) __type44;
      typedef decltype(pythonic::operator_::functor::floordiv()(std::declval<__type26>(), std::declval<__type22>())) __type52;
      typedef decltype(pythonic::operator_::sub(std::declval<__type14>(), std::declval<__type52>())) __type53;
      typedef typename _integ::type<__type1, __type28, __type53, __type36, __type26>::__ptype0 __type58;
      typedef typename __combined<__type28,__type58>::type __type59;
      typedef typename _integ::type<__type1, __type59, __type53, __type36, __type26>::__ptype1 __type60;
      typedef typename __combined<__type53,__type60>::type __type61;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type59>(), std::declval<__type61>(), std::declval<__type36>(), std::declval<__type26>())) __type62;
      typedef decltype(pythonic::operator_::mul(std::declval<__type22>(), std::declval<__type62>())) __type63;
      typedef decltype(pythonic::operator_::sub(std::declval<__type44>(), std::declval<__type63>())) __type64;
      typedef decltype(pythonic::operator_::neg(std::declval<__type64>())) __type65;
      typedef double __type66;
      typedef typename __combined<__type25,__type25>::type __type69;
      typedef decltype(pythonic::operator_::div(std::declval<__type66>(), std::declval<__type69>())) __type70;
      typedef typename pythonic::assignable<decltype(pythonic::operator_::div(std::declval<__type70>(), std::declval<__type69>()))>::type __type72;
      typedef decltype(pythonic::operator_::mul(std::declval<__type65>(), std::declval<__type72>())) __type73;
      typedef decltype(pythonic::operator_::sub(std::declval<__type10>(), std::declval<__type32>())) __type77;
      typedef decltype(pythonic::operator_::sub(std::declval<__type14>(), std::declval<__type26>())) __type80;
      typedef decltype(pythonic::operator_::add(std::declval<__type80>(), std::declval<__type22>())) __type81;
      typedef typename _integ::type<__type1, __type77, __type81, __type39, __type36>::__ptype0 __type86;
      typedef typename __combined<__type77,__type86>::type __type87;
      typedef typename _integ::type<__type1, __type87, __type81, __type39, __type36>::__ptype1 __type88;
      typedef typename __combined<__type81,__type88>::type __type89;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type87>(), std::declval<__type89>(), std::declval<__type39>(), std::declval<__type36>())) __type90;
      typedef decltype(pythonic::operator_::sub(std::declval<__type10>(), std::declval<__type52>())) __type95;
      typedef typename _integ::type<__type1, __type95, __type81, __type26, __type36>::__ptype0 __type104;
      typedef typename __combined<__type95,__type104>::type __type105;
      typedef typename _integ::type<__type1, __type105, __type81, __type26, __type36>::__ptype1 __type106;
      typedef typename __combined<__type81,__type106>::type __type107;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type105>(), std::declval<__type107>(), std::declval<__type26>(), std::declval<__type36>())) __type108;
      typedef decltype(pythonic::operator_::mul(std::declval<__type22>(), std::declval<__type108>())) __type109;
      typedef decltype(pythonic::operator_::sub(std::declval<__type90>(), std::declval<__type109>())) __type110;
      typedef decltype(pythonic::operator_::neg(std::declval<__type110>())) __type111;
      typedef decltype(pythonic::operator_::mul(std::declval<__type111>(), std::declval<__type72>())) __type113;
      typedef decltype(pythonic::operator_::mul(std::declval<__type73>(), std::declval<__type113>())) __type114;
      typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::square{})>::type>::type __type115;
      typedef decltype(pythonic::operator_::add(std::declval<__type14>(), std::declval<__type22>())) __type121;
      typedef typename _integ::type<__type1, __type27, __type121, __type26, __type26>::__ptype0 __type124;
      typedef typename __combined<__type27,__type124>::type __type125;
      typedef typename _integ::type<__type1, __type125, __type121, __type26, __type26>::__ptype1 __type126;
      typedef typename __combined<__type121,__type126>::type __type127;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type125>(), std::declval<__type127>(), std::declval<__type26>(), std::declval<__type26>())) __type128;
      typedef decltype(pythonic::operator_::add(std::declval<__type10>(), std::declval<__type22>())) __type131;
      typedef typename _integ::type<__type1, __type131, __type80, __type26, __type26>::__ptype0 __type137;
      typedef typename __combined<__type131,__type137>::type __type138;
      typedef typename _integ::type<__type1, __type138, __type80, __type26, __type26>::__ptype1 __type139;
      typedef typename __combined<__type80,__type139>::type __type140;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type138>(), std::declval<__type140>(), std::declval<__type26>(), std::declval<__type26>())) __type141;
      typedef decltype(pythonic::operator_::add(std::declval<__type128>(), std::declval<__type141>())) __type142;
      typedef typename _integ::type<__type1, __type27, __type80, __type26, __type26>::__ptype0 __type152;
      typedef typename __combined<__type27,__type152>::type __type153;
      typedef typename _integ::type<__type1, __type153, __type80, __type26, __type26>::__ptype1 __type154;
      typedef typename __combined<__type80,__type154>::type __type155;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type153>(), std::declval<__type155>(), std::declval<__type26>(), std::declval<__type26>())) __type156;
      typedef decltype(pythonic::operator_::sub(std::declval<__type142>(), std::declval<__type156>())) __type157;
      typedef typename _integ::type<__type1, __type131, __type121, __type26, __type26>::__ptype0 __type165;
      typedef typename __combined<__type131,__type165>::type __type166;
      typedef typename _integ::type<__type1, __type166, __type121, __type26, __type26>::__ptype1 __type167;
      typedef typename __combined<__type121,__type167>::type __type168;
      typedef decltype(std::declval<__type18>()(std::declval<__type1>(), std::declval<__type166>(), std::declval<__type168>(), std::declval<__type26>(), std::declval<__type26>())) __type169;
      typedef decltype(pythonic::operator_::sub(std::declval<__type157>(), std::declval<__type169>())) __type170;
      typedef decltype(pythonic::operator_::neg(std::declval<__type170>())) __type171;
      typedef decltype(pythonic::operator_::mul(std::declval<__type171>(), std::declval<__type72>())) __type173;
      typedef decltype(std::declval<__type115>()(std::declval<__type173>())) __type174;
      typedef decltype(pythonic::operator_::mul(std::declval<__type66>(), std::declval<__type174>())) __type175;
      typedef decltype(pythonic::operator_::sub(std::declval<__type114>(), std::declval<__type175>())) __type176;
      typedef container<typename std::remove_reference<__type176>::type> __type177;
      typedef typename pythonic::returnable<typename __combined<__type17,__type177,__type16>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 , typename argument_type1 >
    inline
    typename type<argument_type0, argument_type1>::result_type operator()(argument_type0&& img, argument_type1&& sigma) const
    ;
  }  ;
  template <typename argument_type0 , typename argument_type1 , typename argument_type2 >
  inline
  typename _clip::type<argument_type0, argument_type1, argument_type2>::result_type _clip::operator()(argument_type0&& x, argument_type1&& low, argument_type2&& high) const
  {
    pythonic::pythran_assert(pythonic::operator_::le(0L, low) and pythonic::operator_::le(low, high));
    if (pythonic::operator_::gt(x, high))
    {
      return high;
    }
    else
    {
      if (pythonic::operator_::lt(x, low))
      {
        return low;
      }
      else
      {
        return x;
      }
    }
  }
  template <typename argument_type0 , typename argument_type1 , typename argument_type2 , typename argument_type3 , typename argument_type4 >
  inline
  typename _integ::type<argument_type0, argument_type1, argument_type2, argument_type3, argument_type4>::result_type _integ::operator()(argument_type0&& img, argument_type1&& r, argument_type2&& c, argument_type3&& rl, argument_type4&& cl) const
  {
    typename pythonic::assignable_noescape<decltype(_clip()(r, 0L, pythonic::operator_::sub(std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L)))>::type r__ = _clip()(r, 0L, pythonic::operator_::sub(std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L));
    typename pythonic::assignable_noescape<decltype(_clip()(c, 0L, pythonic::operator_::sub(std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L)))>::type c__ = _clip()(c, 0L, pythonic::operator_::sub(std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L));
    typename pythonic::assignable_noescape<decltype(_clip()(pythonic::operator_::add(r__, rl), 0L, pythonic::operator_::sub(std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L)))>::type r2 = _clip()(pythonic::operator_::add(r__, rl), 0L, pythonic::operator_::sub(std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L));
    typename pythonic::assignable_noescape<decltype(_clip()(pythonic::operator_::add(c__, cl), 0L, pythonic::operator_::sub(std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L)))>::type c2 = _clip()(pythonic::operator_::add(c__, cl), 0L, pythonic::operator_::sub(std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)), 1L));
    return pythonic::builtins::functor::max{}(0.0, pythonic::operator_::sub(pythonic::operator_::sub(pythonic::operator_::add(img.fast(pythonic::types::make_tuple(r__, c__)), img.fast(pythonic::types::make_tuple(r2, c2))), img.fast(pythonic::types::make_tuple(r__, c2))), img.fast(pythonic::types::make_tuple(r2, c__))));
  }
  template <typename argument_type0 , typename argument_type1 >
  inline
  typename _hessian_matrix_det::type<argument_type0, argument_type1>::result_type _hessian_matrix_det::operator()(argument_type0&& img, argument_type1&& sigma) const
  {
    typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::builtins::functor::int_{})>::type>::type __type0;
    typedef long __type1;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type2;
    typedef decltype(pythonic::operator_::mul(std::declval<__type1>(), std::declval<__type2>())) __type3;
    typedef typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type3>()))>::type __type4;
    typedef typename __combined<__type4,__type4>::type __type6;
    typedef decltype(pythonic::operator_::add(std::declval<__type6>(), std::declval<__type1>())) __type7;
    typedef typename __combined<__type6,__type7>::type __type8;
    typedef typename pythonic::assignable<typename pythonic::assignable<decltype(std::declval<__type0>()(std::declval<__type3>()))>::type>::type __type9;
    typedef decltype(pythonic::operator_::add(std::declval<__type9>(), std::declval<__type1>())) __type10;
    typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty_like{})>::type>::type __type11;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type12;
    typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::double_{})>::type>::type __type13;
    typedef typename pythonic::assignable<decltype(std::declval<__type11>()(std::declval<__type12>(), std::declval<__type13>()))>::type __type14;
    typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::builtins::functor::range{})>::type>::type __type15;
    typedef decltype(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, std::declval<__type12>())) __type17;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type17>::type>::type __type18;
    typedef typename pythonic::lazy<__type18>::type __type19;
    typedef decltype(std::declval<__type15>()(std::declval<__type19>())) __type20;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type20>::type::iterator>::value_type>::type __type21;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type17>::type>::type __type22;
    typedef typename pythonic::lazy<__type22>::type __type23;
    typedef decltype(std::declval<__type15>()(std::declval<__type23>())) __type24;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type24>::type::iterator>::value_type>::type __type25;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type21>(), std::declval<__type25>())) __type26;
    typedef indexable<__type26> __type27;
    typedef typename __combined<__type14,__type27>::type __type28;
    typedef _integ __type29;
    typedef typename __combined<__type8,__type1>::type __type32;
    typedef typename pythonic::assignable<decltype(pythonic::operator_::functor::floordiv()(std::declval<__type32>(), std::declval<__type1>()))>::type __type33;
    typedef decltype(pythonic::operator_::sub(std::declval<__type21>(), std::declval<__type33>())) __type34;
    typedef decltype(pythonic::operator_::add(std::declval<__type34>(), std::declval<__type1>())) __type35;
    typedef decltype(pythonic::operator_::sub(std::declval<__type32>(), std::declval<__type1>())) __type38;
    typedef typename pythonic::assignable<decltype(pythonic::operator_::functor::floordiv()(std::declval<__type38>(), std::declval<__type1>()))>::type __type39;
    typedef decltype(pythonic::operator_::sub(std::declval<__type25>(), std::declval<__type39>())) __type40;
    typedef decltype(pythonic::operator_::mul(std::declval<__type1>(), std::declval<__type33>())) __type42;
    typedef decltype(pythonic::operator_::sub(std::declval<__type42>(), std::declval<__type1>())) __type43;
    typedef typename __combined<__type9,__type10>::type __type44;
    typedef typename _integ::type<__type12, __type35, __type40, __type43, __type44>::__ptype0 __type45;
    typedef typename __combined<__type35,__type45>::type __type46;
    typedef typename _integ::type<__type12, __type46, __type40, __type43, __type44>::__ptype1 __type47;
    typedef typename __combined<__type40,__type47>::type __type48;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type46>(), std::declval<__type48>(), std::declval<__type43>(), std::declval<__type44>())) __type49;
    typedef decltype(pythonic::operator_::functor::floordiv()(std::declval<__type33>(), std::declval<__type1>())) __type57;
    typedef decltype(pythonic::operator_::sub(std::declval<__type25>(), std::declval<__type57>())) __type58;
    typedef typename _integ::type<__type12, __type35, __type58, __type43, __type33>::__ptype0 __type63;
    typedef typename __combined<__type35,__type63>::type __type64;
    typedef typename _integ::type<__type12, __type64, __type58, __type43, __type33>::__ptype1 __type65;
    typedef typename __combined<__type58,__type65>::type __type66;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type64>(), std::declval<__type66>(), std::declval<__type43>(), std::declval<__type33>())) __type67;
    typedef decltype(pythonic::operator_::mul(std::declval<__type1>(), std::declval<__type67>())) __type68;
    typedef decltype(pythonic::operator_::sub(std::declval<__type49>(), std::declval<__type68>())) __type69;
    typedef decltype(pythonic::operator_::neg(std::declval<__type69>())) __type70;
    typedef double __type71;
    typedef decltype(pythonic::operator_::div(std::declval<__type71>(), std::declval<__type32>())) __type73;
    typedef typename pythonic::assignable<decltype(pythonic::operator_::div(std::declval<__type73>(), std::declval<__type32>()))>::type __type75;
    typedef decltype(pythonic::operator_::mul(std::declval<__type70>(), std::declval<__type75>())) __type76;
    typedef decltype(pythonic::operator_::sub(std::declval<__type21>(), std::declval<__type39>())) __type80;
    typedef decltype(pythonic::operator_::sub(std::declval<__type25>(), std::declval<__type33>())) __type83;
    typedef decltype(pythonic::operator_::add(std::declval<__type83>(), std::declval<__type1>())) __type84;
    typedef typename _integ::type<__type12, __type80, __type84, __type44, __type43>::__ptype0 __type89;
    typedef typename __combined<__type80,__type89>::type __type90;
    typedef typename _integ::type<__type12, __type90, __type84, __type44, __type43>::__ptype1 __type91;
    typedef typename __combined<__type84,__type91>::type __type92;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type90>(), std::declval<__type92>(), std::declval<__type44>(), std::declval<__type43>())) __type93;
    typedef decltype(pythonic::operator_::sub(std::declval<__type21>(), std::declval<__type57>())) __type98;
    typedef typename _integ::type<__type12, __type98, __type84, __type33, __type43>::__ptype0 __type107;
    typedef typename __combined<__type98,__type107>::type __type108;
    typedef typename _integ::type<__type12, __type108, __type84, __type33, __type43>::__ptype1 __type109;
    typedef typename __combined<__type84,__type109>::type __type110;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type108>(), std::declval<__type110>(), std::declval<__type33>(), std::declval<__type43>())) __type111;
    typedef decltype(pythonic::operator_::mul(std::declval<__type1>(), std::declval<__type111>())) __type112;
    typedef decltype(pythonic::operator_::sub(std::declval<__type93>(), std::declval<__type112>())) __type113;
    typedef decltype(pythonic::operator_::neg(std::declval<__type113>())) __type114;
    typedef decltype(pythonic::operator_::mul(std::declval<__type114>(), std::declval<__type75>())) __type116;
    typedef decltype(pythonic::operator_::mul(std::declval<__type76>(), std::declval<__type116>())) __type117;
    typedef typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::square{})>::type>::type __type118;
    typedef decltype(pythonic::operator_::add(std::declval<__type25>(), std::declval<__type1>())) __type124;
    typedef typename _integ::type<__type12, __type34, __type124, __type33, __type33>::__ptype0 __type127;
    typedef typename __combined<__type34,__type127>::type __type128;
    typedef typename _integ::type<__type12, __type128, __type124, __type33, __type33>::__ptype1 __type129;
    typedef typename __combined<__type124,__type129>::type __type130;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type128>(), std::declval<__type130>(), std::declval<__type33>(), std::declval<__type33>())) __type131;
    typedef decltype(pythonic::operator_::add(std::declval<__type21>(), std::declval<__type1>())) __type134;
    typedef typename _integ::type<__type12, __type134, __type83, __type33, __type33>::__ptype0 __type140;
    typedef typename __combined<__type134,__type140>::type __type141;
    typedef typename _integ::type<__type12, __type141, __type83, __type33, __type33>::__ptype1 __type142;
    typedef typename __combined<__type83,__type142>::type __type143;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type141>(), std::declval<__type143>(), std::declval<__type33>(), std::declval<__type33>())) __type144;
    typedef decltype(pythonic::operator_::add(std::declval<__type131>(), std::declval<__type144>())) __type145;
    typedef typename _integ::type<__type12, __type34, __type83, __type33, __type33>::__ptype0 __type155;
    typedef typename __combined<__type34,__type155>::type __type156;
    typedef typename _integ::type<__type12, __type156, __type83, __type33, __type33>::__ptype1 __type157;
    typedef typename __combined<__type83,__type157>::type __type158;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type156>(), std::declval<__type158>(), std::declval<__type33>(), std::declval<__type33>())) __type159;
    typedef decltype(pythonic::operator_::sub(std::declval<__type145>(), std::declval<__type159>())) __type160;
    typedef typename _integ::type<__type12, __type134, __type124, __type33, __type33>::__ptype0 __type168;
    typedef typename __combined<__type134,__type168>::type __type169;
    typedef typename _integ::type<__type12, __type169, __type124, __type33, __type33>::__ptype1 __type170;
    typedef typename __combined<__type124,__type170>::type __type171;
    typedef decltype(std::declval<__type29>()(std::declval<__type12>(), std::declval<__type169>(), std::declval<__type171>(), std::declval<__type33>(), std::declval<__type33>())) __type172;
    typedef decltype(pythonic::operator_::sub(std::declval<__type160>(), std::declval<__type172>())) __type173;
    typedef decltype(pythonic::operator_::neg(std::declval<__type173>())) __type174;
    typedef decltype(pythonic::operator_::mul(std::declval<__type174>(), std::declval<__type75>())) __type176;
    typedef decltype(std::declval<__type118>()(std::declval<__type176>())) __type177;
    typedef decltype(pythonic::operator_::mul(std::declval<__type71>(), std::declval<__type177>())) __type178;
    typedef decltype(pythonic::operator_::sub(std::declval<__type117>(), std::declval<__type178>())) __type179;
    typedef container<typename std::remove_reference<__type179>::type> __type180;
    typename pythonic::assignable<typename __combined<__type8,__type1>::type>::type size = pythonic::builtins::functor::int_{}(pythonic::operator_::mul(3L, sigma));
    typename pythonic::lazy<decltype(std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)))>::type height = std::get<0>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img));
    typename pythonic::lazy<decltype(std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img)))>::type width = std::get<1>(pythonic::builtins::getattr(pythonic::types::attr::SHAPE{}, img));
    typename pythonic::assignable_noescape<decltype(pythonic::operator_::functor::floordiv()(pythonic::operator_::sub(size, 1L), 2L))>::type s2 = pythonic::operator_::functor::floordiv()(pythonic::operator_::sub(size, 1L), 2L);
    typename pythonic::assignable_noescape<decltype(pythonic::operator_::functor::floordiv()(size, 3L))>::type s3 = pythonic::operator_::functor::floordiv()(size, 3L);
    typename pythonic::assignable<typename __combined<__type9,__type10>::type>::type w = size;
    typename pythonic::assignable<typename __combined<__type28,__type180,__type27>::type>::type out = pythonic::numpy::functor::empty_like{}(img, pythonic::numpy::functor::double_{});
    typename pythonic::assignable_noescape<decltype(pythonic::operator_::div(pythonic::operator_::div(1.0, size), size))>::type w_i = pythonic::operator_::div(pythonic::operator_::div(1.0, size), size);
    if (pythonic::operator_::eq(pythonic::operator_::mod(size, 2L), 0L))
    {
      size += 1L;
    }
    {
      long  __target140036674871248 = height;
      for (long  r=0L; r < __target140036674871248; r += 1L)
      {
        {
          long  __target140036674954912 = width;
          for (long  c=0L; c < __target140036674954912; c += 1L)
          {
            out.fast(pythonic::types::make_tuple(r, c)) = pythonic::operator_::sub(pythonic::operator_::mul(pythonic::operator_::mul(pythonic::operator_::neg(pythonic::operator_::sub(_integ()(img, pythonic::operator_::add(pythonic::operator_::sub(r, s3), 1L), pythonic::operator_::sub(c, s2), pythonic::operator_::sub(pythonic::operator_::mul(2L, s3), 1L), w), pythonic::operator_::mul(3L, _integ()(img, pythonic::operator_::add(pythonic::operator_::sub(r, s3), 1L), pythonic::operator_::sub(c, pythonic::operator_::functor::floordiv()(s3, 2L)), pythonic::operator_::sub(pythonic::operator_::mul(2L, s3), 1L), s3)))), w_i), pythonic::operator_::mul(pythonic::operator_::neg(pythonic::operator_::sub(_integ()(img, pythonic::operator_::sub(r, s2), pythonic::operator_::add(pythonic::operator_::sub(c, s3), 1L), w, pythonic::operator_::sub(pythonic::operator_::mul(2L, s3), 1L)), pythonic::operator_::mul(3L, _integ()(img, pythonic::operator_::sub(r, pythonic::operator_::functor::floordiv()(s3, 2L)), pythonic::operator_::add(pythonic::operator_::sub(c, s3), 1L), s3, pythonic::operator_::sub(pythonic::operator_::mul(2L, s3), 1L))))), w_i)), pythonic::operator_::mul(0.81, pythonic::numpy::functor::square{}(pythonic::operator_::mul(pythonic::operator_::neg(pythonic::operator_::sub(pythonic::operator_::sub(pythonic::operator_::add(_integ()(img, pythonic::operator_::sub(r, s3), pythonic::operator_::add(c, 1L), s3, s3), _integ()(img, pythonic::operator_::add(r, 1L), pythonic::operator_::sub(c, s3), s3, s3)), _integ()(img, pythonic::operator_::sub(r, s3), pythonic::operator_::sub(c, s3), s3, s3)), _integ()(img, pythonic::operator_::add(r, 1L), pythonic::operator_::add(c, 1L), s3, s3))), w_i))));
          }
        }
      }
    }
    return out;
  }
}
#include <pythonic/python/exception_handler.hpp>
#ifdef ENABLE_PYTHON_MODULE
inline
typename __pythran__hessian_det_appx::_hessian_matrix_det::type<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>, double>::result_type _hessian_matrix_det0(pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>&& img, double&& sigma) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran__hessian_det_appx::_hessian_matrix_det()(img, sigma);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}
inline
typename __pythran__hessian_det_appx::_hessian_matrix_det::type<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>, long>::result_type _hessian_matrix_det1(pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>&& img, long&& sigma) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran__hessian_det_appx::_hessian_matrix_det()(img, sigma);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}
inline
typename __pythran__hessian_det_appx::_hessian_matrix_det::type<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>, double>::result_type _hessian_matrix_det2(pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>&& img, double&& sigma) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran__hessian_det_appx::_hessian_matrix_det()(img, sigma);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}
inline
typename __pythran__hessian_det_appx::_hessian_matrix_det::type<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>, long>::result_type _hessian_matrix_det3(pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>&& img, long&& sigma) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran__hessian_det_appx::_hessian_matrix_det()(img, sigma);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}

static PyObject *
__pythran_wrap__hessian_matrix_det0(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[2+1];
    
    char const* keywords[] = {"img", "sigma",  nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "OO",
                                     (char**)keywords , &args_obj[0], &args_obj[1]))
        return nullptr;
    if(is_convertible<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>(args_obj[0]) && is_convertible<double>(args_obj[1]))
        return to_python(_hessian_matrix_det0(from_python<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>(args_obj[0]), from_python<double>(args_obj[1])));
    else {
        return nullptr;
    }
}

static PyObject *
__pythran_wrap__hessian_matrix_det1(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[2+1];
    
    char const* keywords[] = {"img", "sigma",  nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "OO",
                                     (char**)keywords , &args_obj[0], &args_obj[1]))
        return nullptr;
    if(is_convertible<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>(args_obj[0]) && is_convertible<long>(args_obj[1]))
        return to_python(_hessian_matrix_det1(from_python<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>(args_obj[0]), from_python<long>(args_obj[1])));
    else {
        return nullptr;
    }
}

static PyObject *
__pythran_wrap__hessian_matrix_det2(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[2+1];
    
    char const* keywords[] = {"img", "sigma",  nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "OO",
                                     (char**)keywords , &args_obj[0], &args_obj[1]))
        return nullptr;
    if(is_convertible<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>>(args_obj[0]) && is_convertible<double>(args_obj[1]))
        return to_python(_hessian_matrix_det2(from_python<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>>(args_obj[0]), from_python<double>(args_obj[1])));
    else {
        return nullptr;
    }
}

static PyObject *
__pythran_wrap__hessian_matrix_det3(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[2+1];
    
    char const* keywords[] = {"img", "sigma",  nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "OO",
                                     (char**)keywords , &args_obj[0], &args_obj[1]))
        return nullptr;
    if(is_convertible<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>>(args_obj[0]) && is_convertible<long>(args_obj[1]))
        return to_python(_hessian_matrix_det3(from_python<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,pythonic::types::pshape<long,long>>>>(args_obj[0]), from_python<long>(args_obj[1])));
    else {
        return nullptr;
    }
}

            static PyObject *
            __pythran_wrapall__hessian_matrix_det(PyObject *self, PyObject *args, PyObject *kw)
            {
                return pythonic::handle_python_exception([self, args, kw]()
                -> PyObject* {

if(PyObject* obj = __pythran_wrap__hessian_matrix_det0(self, args, kw))
    return obj;
PyErr_Clear();


if(PyObject* obj = __pythran_wrap__hessian_matrix_det1(self, args, kw))
    return obj;
PyErr_Clear();


if(PyObject* obj = __pythran_wrap__hessian_matrix_det2(self, args, kw))
    return obj;
PyErr_Clear();


if(PyObject* obj = __pythran_wrap__hessian_matrix_det3(self, args, kw))
    return obj;
PyErr_Clear();

                return pythonic::python::raise_invalid_argument(
                               "_hessian_matrix_det", "\n""    - _hessian_matrix_det(float64[:,:], float)\n""    - _hessian_matrix_det(float64[:,:], int)", args, kw);
                });
            }


static PyMethodDef Methods[] = {
    {
    "_hessian_matrix_det",
    (PyCFunction)__pythran_wrapall__hessian_matrix_det,
    METH_VARARGS | METH_KEYWORDS,
    "Compute the approximate Hessian Determinant over a 2D image.\n""\n""    Supported prototypes:\n""\n""    - _hessian_matrix_det(float64[:,:], float)\n""    - _hessian_matrix_det(float64[:,:], int)\n""\n""    This method uses box filters over integral images to compute the\n""    approximate Hessian Determinant as described in [1]_.\n""\n""    Parameters\n""    ----------\n""    img : array\n""        The integral image over which to compute Hessian Determinant.\n""    sigma : float\n""        Standard deviation used for the Gaussian kernel, used for the Hessian\n""        matrix\n""\n""    Returns\n""    -------\n""    out : array\n""        The array of the Determinant of Hessians.\n""\n""    References\n""    ----------\n""    .. [1] Herbert Bay, Andreas Ess, Tinne Tuytelaars, Luc Van Gool,\n""           \"SURF: Speeded Up Robust Features\"\n""           ftp://ftp.vision.ee.ethz.ch/publications/articles/eth_biwi_00517.pdf\n""\n""    Notes\n""    -----\n""    The running time of this method only depends on size of the image. It is\n""    independent of `sigma` as one would expect. The downside is that the\n""    result for `sigma` less than `3` is not accurate, i.e., not similar to\n""    the result obtained if someone computed the Hessian and took its\n""    determinant.\n"""},
    {NULL, NULL, 0, NULL}
};


#if PY_MAJOR_VERSION >= 3
  static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "_hessian_det_appx",            /* m_name */
    "",         /* m_doc */
    -1,                  /* m_size */
    Methods,             /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
  };
#define PYTHRAN_RETURN return theModule
#define PYTHRAN_MODULE_INIT(s) PyInit_##s
#else
#define PYTHRAN_RETURN return
#define PYTHRAN_MODULE_INIT(s) init##s
#endif
PyMODINIT_FUNC
PYTHRAN_MODULE_INIT(_hessian_det_appx)(void)
#ifndef _WIN32
__attribute__ ((visibility("default")))
#if defined(GNUC) && !defined(__clang__)
__attribute__ ((externally_visible))
#endif
#endif
;
PyMODINIT_FUNC
PYTHRAN_MODULE_INIT(_hessian_det_appx)(void) {
    import_array()
    #if PY_MAJOR_VERSION >= 3
    PyObject* theModule = PyModule_Create(&moduledef);
    #else
    PyObject* theModule = Py_InitModule3("_hessian_det_appx",
                                         Methods,
                                         ""
    );
    #endif
    if(! theModule)
        PYTHRAN_RETURN;
    PyObject * theDoc = Py_BuildValue("(sss)",
                                      "0.10.0",
                                      "2021-12-03 04:28:03.105633",
                                      "264cbfcf5bc5c4c9747afcf9c5d438f2b4cab047038e53859b294f7ed22f5fc3");
    if(! theDoc)
        PYTHRAN_RETURN;
    PyModule_AddObject(theModule,
                       "__pythran__",
                       theDoc);


    PYTHRAN_RETURN;
}

#endif