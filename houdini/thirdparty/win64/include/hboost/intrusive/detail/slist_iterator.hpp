/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef HBOOST_INTRUSIVE_SLIST_ITERATOR_HPP
#define HBOOST_INTRUSIVE_SLIST_ITERATOR_HPP

#ifndef HBOOST_CONFIG_HPP
#  include <hboost/config.hpp>
#endif

#if defined(HBOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <hboost/intrusive/detail/config_begin.hpp>
#include <hboost/intrusive/detail/workaround.hpp>
#include <hboost/intrusive/detail/std_fwd.hpp>
#include <hboost/intrusive/detail/iiterator.hpp>
#include <hboost/intrusive/detail/mpl.hpp>

namespace hboost {
namespace intrusive {


// slist_iterator provides some basic functions for a
// node oriented bidirectional iterator:
template<class ValueTraits, bool IsConst>
class slist_iterator
{
   private:
   typedef iiterator
      <ValueTraits, IsConst, std::forward_iterator_tag> types_t;

   static const bool stateful_value_traits =                types_t::stateful_value_traits;

   typedef ValueTraits                                      value_traits;
   typedef typename types_t::node_traits                    node_traits;

   typedef typename types_t::node                           node;
   typedef typename types_t::node_ptr                       node_ptr;
   typedef typename types_t::const_value_traits_ptr         const_value_traits_ptr;

   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator()
   {}

   HBOOST_INTRUSIVE_FORCEINLINE explicit slist_iterator(const node_ptr & nodeptr, const const_value_traits_ptr &traits_ptr)
      : members_(nodeptr, traits_ptr)
   {}

   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator(slist_iterator<ValueTraits, false> const& other)
      :  members_(other.pointed_node(), other.get_value_traits())
   {}

   HBOOST_INTRUSIVE_FORCEINLINE const node_ptr &pointed_node() const
   { return members_.nodeptr_; }

   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator &operator=(const node_ptr &node)
   {  members_.nodeptr_ = node;  return static_cast<slist_iterator&>(*this);  }

   HBOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr get_value_traits() const
   {  return members_.get_ptr(); }

   public:
   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator& operator++()
   {
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return static_cast<slist_iterator&> (*this);
   }

   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator operator++(int)
   {
      slist_iterator result (*this);
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return result;
   }

   HBOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const slist_iterator& l, const slist_iterator& r)
   {  return l.pointed_node() == r.pointed_node();   }

   HBOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const slist_iterator& l, const slist_iterator& r)
   {  return !(l == r);   }

   HBOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   {  return *operator->();   }

   HBOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   { return this->operator_arrow(detail::bool_<stateful_value_traits>()); }

   HBOOST_INTRUSIVE_FORCEINLINE slist_iterator<ValueTraits, false> unconst() const
   {  return slist_iterator<ValueTraits, false>(this->pointed_node(), this->get_value_traits());   }

   private:

   HBOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::false_) const
   { return ValueTraits::to_value_ptr(members_.nodeptr_); }

   HBOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::true_) const
   { return this->get_value_traits()->to_value_ptr(members_.nodeptr_); }

   iiterator_members<node_ptr, const_value_traits_ptr, stateful_value_traits> members_;
};

} //namespace intrusive
} //namespace hboost

#include <hboost/intrusive/detail/config_end.hpp>

#endif //HBOOST_INTRUSIVE_SLIST_ITERATOR_HPP
