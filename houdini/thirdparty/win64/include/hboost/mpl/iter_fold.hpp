
#ifndef HBOOST_MPL_ITER_FOLD_HPP_INCLUDED
#define HBOOST_MPL_ITER_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <hboost/mpl/begin_end.hpp>
#include <hboost/mpl/O1_size.hpp>
#include <hboost/mpl/lambda.hpp>
#include <hboost/mpl/aux_/iter_fold_impl.hpp>
#include <hboost/mpl/aux_/na_spec.hpp>
#include <hboost/mpl/aux_/lambda_support.hpp>

namespace hboost { namespace mpl {

template<
      typename HBOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename HBOOST_MPL_AUX_NA_PARAM(State)
    , typename HBOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct iter_fold
{
    typedef typename aux::iter_fold_impl<
          ::hboost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<ForwardOp>::type
        >::state type;

    HBOOST_MPL_AUX_LAMBDA_SUPPORT(3,iter_fold,(Sequence,State,ForwardOp))
};

HBOOST_MPL_AUX_NA_SPEC(3, iter_fold)

}}

#endif // HBOOST_MPL_ITER_FOLD_HPP_INCLUDED
