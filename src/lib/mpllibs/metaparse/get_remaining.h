#ifndef MPLLIBS_PARSER_GET_REMAINING_H
#define MPLLIBS_PARSER_GET_REMAINING_H

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/apply.hpp>
#include <boost/mpl/tag.hpp>

#include <iostream>

namespace mpllibs
{
  namespace metaparse
  {
    template <class p>
    struct get_remaining_impl;
    
    template <class p>
    struct get_remaining :
      boost::mpl::apply<
        mpllibs::metaparse::get_remaining_impl<
          typename boost::mpl::tag<typename p::type>::type
        >,
        typename p::type
      >
    {};
  }
}

#endif

