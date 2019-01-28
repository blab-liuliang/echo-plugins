/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef HBOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP
#define HBOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <hboost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <hboost/mpl/empty.hpp>
#include <hboost/mpl/is_sequence.hpp>

namespace hboost{

namespace multi_index{

namespace detail{

template<typename T>
struct is_index_list
{
  HBOOST_STATIC_CONSTANT(bool,mpl_sequence=mpl::is_sequence<T>::value);
  HBOOST_STATIC_CONSTANT(bool,non_empty=!mpl::empty<T>::value);
  HBOOST_STATIC_CONSTANT(bool,value=mpl_sequence&&non_empty);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace hboost */

#endif
