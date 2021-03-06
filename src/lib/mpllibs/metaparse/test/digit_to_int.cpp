// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/util/digit_to_int.h>

#include "common.h"

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/TestSuite.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>

namespace
{
  const mpllibs::metatest::TestSuite suite("util::digit_to_int");

  typedef
    boost::mpl::equal_to<
      boost::mpl::apply<mpllibs::metaparse::util::digit_to_int, char_0>::type,
      int0
    >
    Test0;

  typedef
    boost::mpl::equal_to<
      boost::mpl::apply<mpllibs::metaparse::util::digit_to_int, char_9>::type,
      int9
    >
    Test9;
}

MPLLIBS_ADD_TEST(suite, Test0)
MPLLIBS_ADD_TEST(suite, Test9)


