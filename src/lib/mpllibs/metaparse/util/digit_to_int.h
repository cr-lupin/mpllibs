#ifndef MPLLIBS_UTIL_DIGIT_TO_INT_H
#define MPLLIBS_UTIL_DIGIT_TO_INT_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/int.hpp>

#include <boost/mpl/integral_c.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    namespace util
    {
      namespace impl
      {
        struct INVALID_DIGIT {};
    
        template <char c>
        struct digit_to_int : INVALID_DIGIT {};
      }

      struct digit_to_int
      {
        template <class d>
        struct apply :
          mpllibs::metaparse::util::impl::digit_to_int<d::type::value>
        {};
      };
    
      namespace impl
      {
        #ifdef _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL
          #error _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL is defined
        #endif
        #define _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL(c, n) \
          template <> struct digit_to_int<c> \
          { \
            typedef boost::mpl::int_<n> type; \
          }
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('0', 0);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('1', 1);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('2', 2);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('3', 3);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('4', 4);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('5', 5);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('6', 6);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('7', 7);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('8', 8);
        _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL('9', 9);
        #undef _MPLLIBS_UTIL_DIGIT_TO_INT_IMPL
      }
    }
  }
}

#endif

