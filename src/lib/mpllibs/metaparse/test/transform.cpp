// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/transform.h>
#include <mpllibs/metaparse/is_error.h>
#include <mpllibs/metaparse/source_position.h>
#include <mpllibs/metaparse/get_result.h>

#include "common.h"

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/TestSuite.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/apply.hpp>

namespace
{
  const mpllibs::metatest::TestSuite suite("transform");

  typedef boost::mpl::always<char_x> transform;
    
  typedef
    boost::mpl::equal_to<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::transform<lit_h, transform>,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      char_x
    >
    TestNormalCase;

  typedef
    mpllibs::metaparse::is_error<
      boost::mpl::apply<
        mpllibs::metaparse::transform<lit_x, transform>,
        str_hello,
        mpllibs::metaparse::start
      >
    >
    TestParserFails;

  typedef
    mpllibs::metaparse::is_error<
      boost::mpl::apply<
        mpllibs::metaparse::transform<lit_h, transform>,
        str_,
        mpllibs::metaparse::start
      >
    >
    TestEmptyInput;
}

MPLLIBS_ADD_TEST(suite, TestNormalCase)
MPLLIBS_ADD_TEST(suite, TestParserFails)
MPLLIBS_ADD_TEST(suite, TestEmptyInput)


