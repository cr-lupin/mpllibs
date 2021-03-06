#ifndef MPLLIBS_UTIL_IS_CHAR_H
#define MPLLIBS_UTIL_IS_CHAR_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/equal_to.hpp>

namespace mpllibs
{
  namespace metaparse
  {
    namespace util
    {
      template <class c>
      struct is_char
      {
        template <class s>
        struct apply : boost::mpl::equal_to<c, s> {};
      };
    }
  }
}

#endif

