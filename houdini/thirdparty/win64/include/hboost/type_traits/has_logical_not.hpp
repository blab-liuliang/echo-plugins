//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef HBOOST_TT_HAS_LOGICAL_NOT_HPP_INCLUDED
#define HBOOST_TT_HAS_LOGICAL_NOT_HPP_INCLUDED

#if defined(__GNUC__) && (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__ > 40800)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#endif

#define HBOOST_TT_TRAIT_NAME has_logical_not
#define HBOOST_TT_TRAIT_OP !
#define HBOOST_TT_FORBIDDEN_IF\
   false

#include <hboost/type_traits/detail/has_prefix_operator.hpp>

#undef HBOOST_TT_TRAIT_NAME
#undef HBOOST_TT_TRAIT_OP
#undef HBOOST_TT_FORBIDDEN_IF

#if defined(__GNUC__) && (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__ > 40800)
#pragma GCC diagnostic pop
#endif

#endif
