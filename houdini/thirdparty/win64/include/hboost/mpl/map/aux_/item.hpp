
#ifndef HBOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
#define HBOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <hboost/mpl/void.hpp>
#include <hboost/mpl/pair.hpp>
#include <hboost/mpl/long.hpp>
#include <hboost/mpl/next.hpp>
#include <hboost/mpl/prior.hpp>
#include <hboost/mpl/map/aux_/map0.hpp>
#include <hboost/mpl/aux_/order_impl.hpp>
#include <hboost/mpl/aux_/yes_no.hpp>
#include <hboost/mpl/aux_/type_wrapper.hpp>
#include <hboost/mpl/aux_/config/arrays.hpp>
#include <hboost/mpl/aux_/config/typeof.hpp>
#include <hboost/mpl/aux_/config/ctps.hpp>


namespace hboost { namespace mpl {

#if defined(HBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Key, typename T, typename Base >
struct m_item
    : Base
{
    typedef Key         key_;
    typedef pair<Key,T> item;
    typedef Base        base;
    typedef m_item      type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(HBOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<HBOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[HBOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<T>, VALUE_BY_KEY, m_item, aux::type_wrapper<Key>* );
    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<item>, ITEM_BY_ORDER, m_item, order* );
    HBOOST_MPL_AUX_MAP_OVERLOAD( order_tag_, ORDER_BY_KEY, m_item, aux::type_wrapper<Key>* );
};


template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;
    typedef m_mask  type;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<void_>, VALUE_BY_KEY, m_mask, aux::type_wrapper<Key>* );
    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<void_>, ITEM_BY_ORDER, m_mask, key_order_* );
};

#else // HBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES


#   if !defined(HBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n, typename Key, typename T, typename Base >
struct m_item;

#   else

template< long n >
struct m_item_impl
{
    template< typename Key, typename T, typename Base >
    struct result_;
};

template< long n, typename Key, typename T, typename Base >
struct m_item
    : m_item_impl<n>::result_<Key,T,Base>
{
};


#   endif


template< typename Key, typename T, typename Base >
struct m_item_
    : Base
{
    typedef Key     key_;
    typedef Base    base;
    typedef m_item_ type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(HBOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<HBOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[HBOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    HBOOST_MPL_AUX_MAP_OVERLOAD( order_tag_, ORDER_BY_KEY, m_item_, aux::type_wrapper<Key>* );
};

template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;
    typedef m_mask  type;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::no_tag, ORDER_BY_KEY, m_mask, aux::type_wrapper<Key>* );
    HBOOST_MPL_AUX_MAP_OVERLOAD( aux::yes_tag, IS_MASKED, m_mask, key_order_* );
};

#endif // HBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // HBOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
