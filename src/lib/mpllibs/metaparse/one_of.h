#ifndef MPLLIBS_PARSER_ONE_OF_H
#define MPLLIBS_PARSER_ONE_OF_H

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mpllibs/metaparse/is_error.h>
#include <mpllibs/metaparse/fail.h>

#include <mpllibs/metaparse/util/define_data.h>

#include <mpllibs/metatest/to_stream.h>

#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#ifndef PARSER_ONE_OF_MAX_ARGUMENT
  #define PARSER_ONE_OF_MAX_ARGUMENT 20
#endif

namespace mpllibs
{
  namespace metaparse
  {
    namespace errors
    {
      MPLLIBS_METAPARSE_DEFINE_DATA(none_of_the_expected_cases_found);
    }
  
    #ifdef PARSER_ONE_OF_BODY_PREFIX
      #error PARSER_ONE_OF_BODY_PREFIX already defined
    #endif
    #define PARSER_ONE_OF_BODY_PREFIX(z, n, unused) \
      typename boost::mpl::if_< \
        boost::mpl::not_< \
          typename mpllibs::metaparse::is_error< \
            boost::mpl::apply<p##n, s, pos> \
          >::type \
        >, \
        p##n, \
    
    #ifdef PARSER_ONE_OF_BODY_POSTFIX
      #error PARSER_ONE_OF_BODY_POSTFIX already defined
    #endif
    #define PARSER_ONE_OF_BODY_POSTFIX(z, n, unused) \
      >::type
  
    #ifdef MPLLIBS_PARSER_ONE_OF
      #error MPLLIBS_PARSER_ONE_OF already defined
    #endif
    // We need mock otherwise n = 0 wouldn't compile
    #define MPLLIBS_PARSER_ONE_OF(z, n, unused) \
      template < \
        BOOST_PP_ENUM_PARAMS(n, class p) \
        BOOST_PP_COMMA_IF(n) \
        class mock = int \
      > \
      struct one_of_##n \
      { \
        template <class s, class pos> \
        struct apply : \
          boost::mpl::apply< \
            BOOST_PP_REPEAT(n, PARSER_ONE_OF_BODY_PREFIX, ~) \
              mpllibs::metaparse::fail< \
                mpllibs::metaparse::errors::none_of_the_expected_cases_found \
              > \
            BOOST_PP_REPEAT(n, PARSER_ONE_OF_BODY_POSTFIX, ~), \
            s, \
            pos \
          > \
        {}; \
      };
    
    BOOST_PP_REPEAT(PARSER_ONE_OF_MAX_ARGUMENT, MPLLIBS_PARSER_ONE_OF, ~)
    
    #undef MPLLIBS_PARSER_ONE_OF
    #undef PARSER_ONE_OF_BODY_POSTFIX
    #undef PARSER_ONE_OF_BODY_PREFIX
    
    struct unused_one_of_argument;
  
    template <
      BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
        PARSER_ONE_OF_MAX_ARGUMENT,
        class p,
        mpllibs::metaparse::unused_one_of_argument
      ),
      class mock = int
    >
    struct one_of;
    
    #ifdef PARSER_ONE_OF_UNUSED_PARAM
      #error PARSER_ONE_OF_UNUSED_PARAM already defined
    #endif
    #define PARSER_ONE_OF_UNUSED_PARAM(z, n, unused) \
      BOOST_PP_COMMA_IF(n) mpllibs::metaparse::unused_one_of_argument
    
    #ifdef PARSER_ONE_OF_CASE
      #error PARSER_ONE_OF_CASE already defined
    #endif
    #define PARSER_ONE_OF_CASE(z, n, unused) \
      template <BOOST_PP_ENUM_PARAMS(n, class p)> \
      struct one_of< \
        BOOST_PP_ENUM_PARAMS(n, p) \
        BOOST_PP_COMMA_IF(n) \
        BOOST_PP_REPEAT( \
          BOOST_PP_SUB(PARSER_ONE_OF_MAX_ARGUMENT, n), \
          PARSER_ONE_OF_UNUSED_PARAM, \
          ~ \
        ) \
      > : \
        mpllibs::metaparse::one_of_##n<BOOST_PP_ENUM_PARAMS(n, p)> \
      {};
    
    BOOST_PP_REPEAT(PARSER_ONE_OF_MAX_ARGUMENT, PARSER_ONE_OF_CASE, ~)
    
    #undef PARSER_ONE_OF_CASE
    #undef PARSER_ONE_OF_UNUSED_PARAM
  }
}

DEFINE_TO_STREAM_FOR_TYPE(
  mpllibs::metaparse::errors::none_of_the_expected_cases_found,
  "None of the expected cases found"
)

#endif

