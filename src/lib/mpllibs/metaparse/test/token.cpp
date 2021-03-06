// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/token.h>
#include <mpllibs/metaparse/keyword.h>
#include <mpllibs/metaparse/is_error.h>
#include <mpllibs/metaparse/source_position.h>
#include <mpllibs/metaparse/get_result.h>
#include <mpllibs/metaparse/get_remaining.h>

#include "common.h"

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/TestSuite.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>

namespace
{
  const mpllibs::metatest::TestSuite suite("token");

  typedef
    boost::mpl::list_c<char, 'h', 'e', 'l', 'l', 'o', ' ', '\t'>
    str_hello_t;
      
  typedef mpllibs::metaparse::keyword<str_hello, int13> testParser;

  typedef
    boost::mpl::equal_to<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::token<testParser>,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      mpllibs::metaparse::get_result<
        boost::mpl::apply<testParser, str_hello, mpllibs::metaparse::start>
      >::type
    >
    TestNoSpace;

  typedef
    boost::mpl::equal_to<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::token<testParser>,
          str_hello_t,
          mpllibs::metaparse::start
        >
      >::type,
      mpllibs::metaparse::get_result<
        boost::mpl::apply<testParser, str_hello, mpllibs::metaparse::start>
      >::type
    >
    TestSpaces;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_remaining<
        boost::mpl::apply<
          mpllibs::metaparse::token<testParser>,
          str_hello_t,
          mpllibs::metaparse::start
        >
      >::type,
      str_
    >
    TestSpacesConsumed;

  typedef
    mpllibs::metaparse::is_error<
      boost::mpl::apply<
        mpllibs::metaparse::token<testParser>,
        str_,
        mpllibs::metaparse::start
      >
    >
    TestFail;
}

MPLLIBS_ADD_TEST(suite, TestNoSpace)
MPLLIBS_ADD_TEST(suite, TestSpaces)
MPLLIBS_ADD_TEST(suite, TestSpacesConsumed)
MPLLIBS_ADD_TEST(suite, TestFail)


