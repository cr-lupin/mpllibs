// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/any_one_of.h>
#include <mpllibs/metaparse/one_char.h>
#include <mpllibs/metaparse/fail.h>
#include <mpllibs/metaparse/keyword.h>
#include <mpllibs/metaparse/source_position.h>
#include <mpllibs/metaparse/get_result.h>

#include <mpllibs/metaparse/util/define_data.h>

#include "common.h"

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/TestSuite.h>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/equal.hpp>

namespace
{
  const mpllibs::metatest::TestSuite suite("any_one_of");

  MPLLIBS_METAPARSE_DEFINE_DATA(test_error);
  
  typedef mpllibs::metaparse::fail<test_error> test_fail;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of< >,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list<>
    >
    Test0;
  
  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of<mpllibs::metaparse::one_char>,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list<char_h, char_e, char_l, char_l, char_o>
    >
    TestGoodSequence;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of<test_fail>,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list< >
    >
    Test1WithBad;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of<
            mpllibs::metaparse::one_char,
            test_fail
          >,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list<char_h, char_e, char_l, char_l, char_o>
    >
    Test2WithFirstGood;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of<
            test_fail,
            mpllibs::metaparse::one_char
          >,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list<char_h, char_e, char_l, char_l, char_o>
    >
    Test2WithSecondGood;

  typedef
    boost::mpl::equal<
      mpllibs::metaparse::get_result<
        boost::mpl::apply<
          mpllibs::metaparse::any_one_of<
            mpllibs::metaparse::keyword<boost::mpl::string<'h'>, char_h>,
            mpllibs::metaparse::keyword<boost::mpl::string<'e'>, char_e>,
            mpllibs::metaparse::keyword<boost::mpl::string<'l'>, char_l>
          >,
          str_hello,
          mpllibs::metaparse::start
        >
      >::type,
      boost::mpl::list<char_h, char_e, char_l, char_l>
    >
    TestAcceptAnyArgument;
}

MPLLIBS_ADD_TEST(suite, Test0)
MPLLIBS_ADD_TEST(suite, TestGoodSequence)
MPLLIBS_ADD_TEST(suite, Test1WithBad)
MPLLIBS_ADD_TEST(suite, Test2WithFirstGood)
MPLLIBS_ADD_TEST(suite, Test2WithSecondGood)
MPLLIBS_ADD_TEST(suite, TestAcceptAnyArgument)

