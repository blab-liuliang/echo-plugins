
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(HBOOST_VMD_LIST_TO_TUPLE_HPP)
#define HBOOST_VMD_LIST_TO_TUPLE_HPP

#include <hboost/vmd/detail/setup.hpp>

#if HBOOST_PP_VARIADICS

#include <hboost/preprocessor/control/iif.hpp>
#include <hboost/preprocessor/list/to_tuple.hpp>
#include <hboost/vmd/empty.hpp>
#include <hboost/vmd/is_empty_list.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def HBOOST_VMD_LIST_TO_TUPLE(list)

    \brief converts a list to a tuple.

    list = list to be converted.
    
    If the list is an empty list (HBOOST_PP_NIL) it is converted to an empty tuple.
    Otherwise the list is converted to a tuple with the same number of elements as the list.
*/

#define HBOOST_VMD_LIST_TO_TUPLE(list) \
    HBOOST_PP_IIF \
        ( \
        HBOOST_VMD_IS_EMPTY_LIST(list), \
        HBOOST_VMD_EMPTY, \
        HBOOST_PP_LIST_TO_TUPLE \
        ) \
    (list) \
/**/

#endif /* HBOOST_PP_VARIADICS */
#endif /* HBOOST_VMD_LIST_TO_TUPLE_HPP */
