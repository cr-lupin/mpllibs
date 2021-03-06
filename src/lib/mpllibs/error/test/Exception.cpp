// Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/error/Exception.h>
#include <mpllibs/error/do_.h>

#include <mpllibs/error/get_data.h>

#include <mpllibs/metatest/test.h>
#include <mpllibs/metatest/TestSuite.h>

#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/always.hpp>
#include <boost/type_traits/is_same.hpp>

#include "common.h"

namespace
{
  const mpllibs::metatest::TestSuite suite("Exception");
  
  typedef mpllibs::error::Exception<int13> e;

  typedef
    boost::mpl::equal_to<int13, mpllibs::error::get_data<e>::type>
    TestGetData;

  typedef
    boost::mpl::equal_to<
      int13,
      DO<mpllibs::error::ExceptionMonad>::apply<
        RETURN<int13>
      >::type::type
    >
    TestMonadicNoException;

  typedef
    boost::mpl::equal_to<
      int13,
      mpllibs::error::get_data<
        DO<mpllibs::error::ExceptionMonad>::apply<
          boost::mpl::apply<boost::mpl::always<e>, int>
        >::type
      >::type
    >
    TestMonadicException;


  typedef
    boost::mpl::equal_to<
      int13,
      mpllibs::error::get_data<
        DO<mpllibs::error::ExceptionMonad>::apply<
          boost::mpl::apply<boost::mpl::always<e>, int>,
          RETURN<int13>
        >::type
      >::type
    >
    TestExceptionPropagation;


  typedef
    boost::is_same<
      mpllibs::error::NoException_tag,
      boost::mpl::tag<
        mpllibs::error::return_<mpllibs::error::ExceptionMonad, int13>::type
      >::type
    >
    TestReturnTag;

  typedef
    boost::is_same<
      mpllibs::error::NoException_tag,
      boost::mpl::tag<
        DO<mpllibs::error::ExceptionMonad>::apply<
          RETURN<int11>
        >::type
      >::type
    >
    TestTagWith1ElementDo;

  typedef
    boost::mpl::equal_to<
      int11,
      DO<mpllibs::error::ExceptionMonad>::apply<
        RETURN<int13>,
        RETURN<int11>
      >::type::type // the last ::type unwraps the value
    >
    TestExecutionSequence;
  
  struct x;
  
  typedef
    boost::mpl::equal_to<
      int13,
      mpllibs::error::get_data<
        DO<mpllibs::error::ExceptionMonad>::apply<
          SET<x, boost::mpl::apply<boost::mpl::always<e>, int> >,
          RETURN<int13>
        >::type
      >::type
    >
    TestExceptionInSet;
}

MPLLIBS_ADD_TEST(suite, TestGetData)

MPLLIBS_ADD_TEST(suite, TestMonadicNoException)
MPLLIBS_ADD_TEST(suite, TestMonadicException)
MPLLIBS_ADD_TEST(suite, TestExceptionPropagation)
MPLLIBS_ADD_TEST(suite, TestTagWith1ElementDo)
MPLLIBS_ADD_TEST(suite, TestReturnTag)
MPLLIBS_ADD_TEST(suite, TestExecutionSequence)
MPLLIBS_ADD_TEST(suite, TestExceptionInSet)


