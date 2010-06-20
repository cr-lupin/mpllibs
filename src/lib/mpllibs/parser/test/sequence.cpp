// Copyright Abel Sinkovics (abel@sinkovics.hu) 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/parser/sequence.h>
#include <mpllibs/parser/lit.h>

#include <mpllibs/test/test.h>

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/equal_to.hpp>

namespace
{
  typedef boost::mpl::integral_c<char, 'h'> hCharacter;
  typedef boost::mpl::integral_c<char, 'e'> eCharacter;
  typedef boost::mpl::integral_c<char, 'x'> xCharacter;
      
  typedef boost::mpl::list_c<char, 'h', 'e', 'l', 'l', 'o'> helloString;
  typedef boost::mpl::list_c<char> emptyString;

  typedef
    boost::mpl::equal_to<
      mpllibs::parser::sequence<
        mpllibs::parser::lit<hCharacter>,
        mpllibs::parser::lit<eCharacter>
      >::apply<helloString>::type::first,
      mpllibs::util::pair<hCharacter, eCharacter>
    >::type
    Sequence_TestTwoChars;

  typedef
    boost::mpl::equal_to<
      mpllibs::parser::sequence<
        mpllibs::parser::lit<xCharacter>,
        mpllibs::parser::lit<eCharacter>
      >::apply<helloString>::type,
      mpllibs::parser::nothing
    >::type
    Sequence_TestFirstFails;

  typedef
    boost::mpl::equal_to<
      mpllibs::parser::sequence<
        mpllibs::parser::lit<hCharacter>,
        mpllibs::parser::lit<xCharacter>
      >::apply<helloString>::type,
      mpllibs::parser::nothing
    >::type
    Sequence_TestSecondFails;

  typedef
    boost::mpl::equal_to<
      mpllibs::parser::sequence<
        mpllibs::parser::lit<hCharacter>,
        mpllibs::parser::lit<eCharacter>
      >::apply<emptyString>::type,
      mpllibs::parser::nothing
    >::type
    Sequence_TestEmptyInput;
}

MPLLIBS_ADD_TEST(Sequence_TestTwoChars)
MPLLIBS_ADD_TEST(Sequence_TestFirstFails)
MPLLIBS_ADD_TEST(Sequence_TestSecondFails)
MPLLIBS_ADD_TEST(Sequence_TestEmptyInput)

