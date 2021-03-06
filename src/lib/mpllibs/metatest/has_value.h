#ifndef MPLLIBS_TEST_HAS_VALUE_H
#define MPLLIBS_TEST_HAS_VALUE_H

// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metatest/yes.h>
#include <mpllibs/metatest/no.h>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c.hpp>

namespace mpllibs
{
  namespace metatest
  {
    // Based on C++ Template Metaprogramming, chapter 9.10
    template <class F, class ValueType>
    struct has_value
    {
      struct type
      {
        template <ValueType value_>
        struct value_wrapper;
        
        // It needs an extra int argument to remove ambiguity between
        // this version and the one with ...
        template <class T>
        static
          typename
            boost::mpl::apply<
              boost::mpl::always<mpllibs::metatest::yes>,
              boost::mpl::integral_c<ValueType, T::value>
            >::type
          tester(T*, int);
      
        // I have to pass a T* argument to make Visual C++ accept it
        template <class T>
        static mpllibs::metatest::no tester(T*, ...);
      
        static const bool
          value =
            sizeof(
              mpllibs::metatest::has_value<F, ValueType>::type::tester(
                static_cast<F*>(0),
                13
              )
            )
            == sizeof(mpllibs::metatest::yes);
      };
    };
  }
}

#endif

