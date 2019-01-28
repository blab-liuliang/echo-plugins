//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef HBOOST_CONTAINER_SET_HPP
#define HBOOST_CONTAINER_SET_HPP

#ifndef HBOOST_CONFIG_HPP
#  include <hboost/config.hpp>
#endif

#if defined(HBOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <hboost/container/detail/config_begin.hpp>
#include <hboost/container/detail/workaround.hpp>
// container
#include <hboost/container/container_fwd.hpp>
// container/detail
#include <hboost/container/detail/mpl.hpp>
#include <hboost/container/detail/tree.hpp>
#include <hboost/container/new_allocator.hpp> //new_allocator
// intrusive/detail
#include <hboost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <hboost/intrusive/detail/minimal_less_equal_header.hpp>//less, equal
// move
#include <hboost/move/traits.hpp>
#include <hboost/move/utility_core.hpp>
// move/detail
#include <hboost/move/detail/move_helpers.hpp>
#if defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <hboost/move/detail/fwd_macros.hpp>
#endif
// std
#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace hboost {
namespace container {

#ifdef HBOOST_CONTAINER_DOXYGEN_INVOKED

//! A set is a kind of associative container that supports unique keys (contains at
//! most one of each key value) and provides for fast retrieval of the keys themselves.
//! Class set supports bidirectional iterators.
//!
//! A set satisfies all of the requirements of a container and of a reversible container
//! , and of an associative container. A set also provides most operations described in
//! for unique keys.
//!
//! \tparam Key is the type to be inserted in the set, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam Allocator is the allocator to be used to allocate memory for this container
//! \tparam SetOptions is an packed option type generated using using hboost::container::tree_assoc_options.
template <class Key, class Compare = std::less<Key>, class Allocator = new_allocator<Key>, class SetOptions = tree_assoc_defaults >
#else
template <class Key, class Compare, class Allocator, class SetOptions>
#endif
class set
   ///@cond
   : public container_detail::tree
      < Key, Key, container_detail::identity<Key>, Compare, Allocator, SetOptions>
   ///@endcond
{
   #ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   HBOOST_COPYABLE_AND_MOVABLE(set)
   typedef container_detail::tree
      < Key, Key, container_detail::identity<Key>, Compare, Allocator, SetOptions> base_t;
   #endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                         key_type;
   typedef Key                                                                         value_type;
   typedef Compare                                                                     key_compare;
   typedef Compare                                                                     value_compare;
   typedef ::hboost::container::allocator_traits<Allocator>                             allocator_traits_type;
   typedef typename ::hboost::container::allocator_traits<Allocator>::pointer           pointer;
   typedef typename ::hboost::container::allocator_traits<Allocator>::const_pointer     const_pointer;
   typedef typename ::hboost::container::allocator_traits<Allocator>::reference         reference;
   typedef typename ::hboost::container::allocator_traits<Allocator>::const_reference   const_reference;
   typedef typename ::hboost::container::allocator_traits<Allocator>::size_type         size_type;
   typedef typename ::hboost::container::allocator_traits<Allocator>::difference_type   difference_type;
   typedef Allocator                                                                   allocator_type;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)              stored_allocator_type;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::iterator)                           iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::const_iterator)                     const_iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                   reverse_iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)             const_reverse_iterator;

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty set.
   //!
   //! <b>Complexity</b>: Constant.
   set()
      : base_t()
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object
   //! and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   explicit set(const Compare& comp,
                const allocator_type& a = allocator_type())
      : base_t(comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified allocator object.
   //!
   //! <b>Complexity</b>: Constant.
   explicit set(const allocator_type& a)
      : base_t(a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   set(InputIterator first, InputIterator last, const Compare& comp = Compare(),
         const allocator_type& a = allocator_type())
      : base_t(true, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   set(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(true, first, last, key_compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   set( ordered_unique_range_t, InputIterator first, InputIterator last
      , const Compare& comp = Compare(), const allocator_type& a = allocator_type())
      : base_t(ordered_range, first, last, comp, a)
   {}

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   set(std::initializer_list<value_type> il, const Compare& comp = Compare(), const allocator_type& a = allocator_type())
      : base_t(true, il.begin(), il.end(), comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   set(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(true, il.begin(), il.end(), Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   set( ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp = Compare()
      , const allocator_type& a = allocator_type())
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! <b>Effects</b>: Copy constructs a set.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   set(const set& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! <b>Effects</b>: Move constructs a set. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   set(HBOOST_RV_REF(set) x)
      : base_t(HBOOST_MOVE_BASE(base_t, x))
   {}

   //! <b>Effects</b>: Copy constructs a set using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   set(const set& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! <b>Effects</b>: Move constructs a set using the specified allocator.
   //!                 Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   set(HBOOST_RV_REF(set) x, const allocator_type &a)
      : base_t(HBOOST_MOVE_BASE(base_t, x), a)
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   set& operator=(HBOOST_COPY_ASSIGN_REF(set) x)
   {  return static_cast<set&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! <b>Effects</b>: this->swap(x.get()).
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   set& operator=(HBOOST_RV_REF(set) x)
      HBOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && hboost::container::container_detail::is_nothrow_move_assignable<Compare>::value )
   {  return static_cast<set&>(this->base_t::operator=(HBOOST_MOVE_BASE(base_t, x)));  }

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Copy all elements from il to *this.
   //!
   //! <b>Complexity</b>: Linear in il.size().
   set& operator=(std::initializer_list<value_type> il)
   {
      this->clear();
      insert(il.begin(), il.end());
      return *this;
   }
#endif

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Returns a copy of the allocator that
   //!   was passed to the object's constructor.
   //!
   //! <b>Complexity</b>: Constant.
   allocator_type get_allocator() const;

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   stored_allocator_type &get_stored_allocator();

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   const stored_allocator_type &get_stored_allocator() const;

   //! <b>Effects</b>: Returns an iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant
   iterator begin();

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const;

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const;

   //! <b>Effects</b>: Returns an iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator end();

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const;

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin();

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend();

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const;

   //! <b>Effects</b>: Returns true if the container contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   bool empty() const;

   //! <b>Effects</b>: Returns the number of the elements contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const;

   //! <b>Effects</b>: Returns the largest possible size of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type max_size() const;
   #endif   //   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   #if !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>:  Inserts an object x of type Key constructed with
   //!   std::forward<Args>(args)... if and only if there is
   //!   no element in the container with equivalent value.
   //!   and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   Key's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   std::pair<iterator,bool> emplace(HBOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_unique(hboost::forward<Args>(args)...); }

   //! <b>Effects</b>:  Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... if and only if there is
   //!   no element in the container with equivalent value.
   //!   p is a hint pointing to where the insert
   //!   should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   iterator emplace_hint(const_iterator p, HBOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_hint_unique(p, hboost::forward<Args>(args)...); }

   #else // !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define HBOOST_CONTAINER_SET_EMPLACE_CODE(N) \
   HBOOST_MOVE_TMPL_LT##N HBOOST_MOVE_CLASS##N HBOOST_MOVE_GT##N \
   std::pair<iterator,bool> emplace(HBOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_unique(HBOOST_MOVE_FWD##N);  }\
   \
   HBOOST_MOVE_TMPL_LT##N HBOOST_MOVE_CLASS##N HBOOST_MOVE_GT##N \
   iterator emplace_hint(const_iterator hint HBOOST_MOVE_I##N HBOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_unique(hint HBOOST_MOVE_I##N HBOOST_MOVE_FWD##N); }\
   //
   HBOOST_MOVE_ITERATE_0TO9(HBOOST_CONTAINER_SET_EMPLACE_CODE)
   #undef HBOOST_CONTAINER_SET_EMPLACE_CODE

   #endif   // !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x if and only if there is no element in the container
   //!   with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   std::pair<iterator, bool> insert(const value_type &x);

   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   std::pair<iterator, bool> insert(value_type &&x);
   #else
   private:
   typedef std::pair<iterator, bool> insert_return_pair;
   public:
   HBOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, insert_return_pair, this->priv_insert)
   #endif

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts an element move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator insert(const_iterator p, value_type &&x);
   #else
   HBOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_unique(first, last);  }

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(),il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_unique(il.begin(), il.end()); }
#endif

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Amortized constant time
   iterator erase(const_iterator p);

   //! <b>Effects</b>: Erases all elements in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements.
   //!
   //! <b>Complexity</b>: log(size()) + count(k)
   size_type erase(const key_type& x);

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: log(size())+N where N is the distance from first to last.
   iterator erase(const_iterator first, const_iterator last);

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(set& x)
      HBOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && hboost::container::container_detail::is_nothrow_swappable<Compare>::value );

   //! <b>Effects</b>: erase(a.begin(),a.end()).
   //!
   //! <b>Postcondition</b>: size() == 0.
   //!
   //! <b>Complexity</b>: linear in size().
   void clear();

   //! <b>Effects</b>: Returns the comparison object out
   //!   of which a was constructed.
   //!
   //! <b>Complexity</b>: Constant.
   key_compare key_comp() const;

   //! <b>Effects</b>: Returns an object of value_compare constructed out
   //!   of the comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   value_compare value_comp() const;

   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator find(const key_type& x);

   //! <b>Returns</b>: A const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   const_iterator find(const key_type& x) const;

   #endif   //#if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->base_t::find(x) != this->base_t::cend());  }

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   size_type count(const key_type& x)
   {  return static_cast<size_type>(this->base_t::find(x) != this->base_t::end());  }

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than k, or a.end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   iterator lower_bound(const key_type& x);

   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than k, or a.end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   const_iterator lower_bound(const key_type& x) const;

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   iterator upper_bound(const key_type& x);

   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   const_iterator upper_bound(const key_type& x) const;

   #endif   //#if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<iterator,iterator> equal_range(const key_type& x)
   {  return this->base_t::lower_bound_range(x);  }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
   {  return this->base_t::lower_bound_range(x);  }

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;

   //! <b>Effects</b>: Rebalances the tree. It's a no-op for Red-Black and AVL trees.
   //!
   //! <b>Complexity</b>: Linear
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const set& x, const set& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(set& x, set& y);

   #endif   //#if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   template <class KeyType>
   std::pair<iterator, bool> priv_insert(HBOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_unique(::hboost::forward<KeyType>(x));  }

   template <class KeyType>
   iterator priv_insert(const_iterator p, HBOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_unique(p, ::hboost::forward<KeyType>(x)); }
   #endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class SetOptions, class Allocator>
struct has_trivial_destructor_after_move<hboost::container::set<Key, Compare, Allocator, SetOptions> >
{
   typedef typename ::hboost::container::allocator_traits<Allocator>::pointer pointer;
   static const bool value = ::hboost::has_trivial_destructor_after_move<Allocator>::value &&
                             ::hboost::has_trivial_destructor_after_move<pointer>::value &&
                             ::hboost::has_trivial_destructor_after_move<Compare>::value;
};

namespace container {

#endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

#ifdef HBOOST_CONTAINER_DOXYGEN_INVOKED

//! A multiset is a kind of associative container that supports equivalent keys
//! (possibly contains multiple copies of the same key value) and provides for
//! fast retrieval of the keys themselves. Class multiset supports bidirectional iterators.
//!
//! A multiset satisfies all of the requirements of a container and of a reversible
//! container, and of an associative container). multiset also provides most operations
//! described for duplicate keys.
//!
//! \tparam Key is the type to be inserted in the set, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam Allocator is the allocator to be used to allocate memory for this container
//! \tparam MultiSetOptions is an packed option type generated using using hboost::container::tree_assoc_options.
template <class Key, class Compare = std::less<Key>, class Allocator = new_allocator<Key>, class MultiSetOptions = tree_assoc_defaults >
#else
template <class Key, class Compare, class Allocator, class MultiSetOptions>
#endif
class multiset
   /// @cond
   : public container_detail::tree
      <Key, Key,container_detail::identity<Key>, Compare, Allocator, MultiSetOptions>
   /// @endcond
{
   #ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   HBOOST_COPYABLE_AND_MOVABLE(multiset)
   typedef container_detail::tree
      <Key, Key,container_detail::identity<Key>, Compare, Allocator, MultiSetOptions> base_t;
   #endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

   public:

   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                         key_type;
   typedef Key                                                                         value_type;
   typedef Compare                                                                     key_compare;
   typedef Compare                                                                     value_compare;
   typedef ::hboost::container::allocator_traits<Allocator>                             allocator_traits_type;
   typedef typename ::hboost::container::allocator_traits<Allocator>::pointer           pointer;
   typedef typename ::hboost::container::allocator_traits<Allocator>::const_pointer     const_pointer;
   typedef typename ::hboost::container::allocator_traits<Allocator>::reference         reference;
   typedef typename ::hboost::container::allocator_traits<Allocator>::const_reference   const_reference;
   typedef typename ::hboost::container::allocator_traits<Allocator>::size_type         size_type;
   typedef typename ::hboost::container::allocator_traits<Allocator>::difference_type   difference_type;
   typedef Allocator                                                                   allocator_type;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)              stored_allocator_type;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::iterator)                           iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::const_iterator)                     const_iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                   reverse_iterator;
   typedef typename HBOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)             const_reverse_iterator;

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! @copydoc ::hboost::container::set::set()
   multiset()
      : base_t()
   {}

   //! @copydoc ::hboost::container::set::set(const Compare&, const allocator_type&)
   explicit multiset(const Compare& comp,
                     const allocator_type& a = allocator_type())
      : base_t(comp, a)
   {}

   //! @copydoc ::hboost::container::set::set(const allocator_type&)
   explicit multiset(const allocator_type& a)
      : base_t(a)
   {}

   //! @copydoc ::hboost::container::set::set(InputIterator, InputIterator, const Compare& comp, const allocator_type&)
   template <class InputIterator>
   multiset(InputIterator first, InputIterator last,
            const Compare& comp = Compare(),
            const allocator_type& a = allocator_type())
      : base_t(false, first, last, comp, a)
   {}

   //! @copydoc ::hboost::container::set::set(InputIterator, InputIterator, const allocator_type&)
   template <class InputIterator>
   multiset(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(false, first, last, key_compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty multiset using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   multiset( ordered_range_t, InputIterator first, InputIterator last
           , const Compare& comp = Compare()
           , const allocator_type& a = allocator_type())
      : base_t(ordered_range, first, last, comp, a)
   {}

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::hboost::container::set::set(std::initializer_list<value_type>, const Compare& comp, const allocator_type&)
   multiset(std::initializer_list<value_type> il, const Compare& comp = Compare(), const allocator_type& a = allocator_type())
      : base_t(false, il.begin(), il.end(), comp, a)
   {}

   //! @copydoc ::hboost::container::set::set(std::initializer_list<value_type>, const allocator_type&)
   multiset(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(false, il.begin(), il.end(), Compare(), a)
   {}

   //! @copydoc ::hboost::container::set::set(ordered_unique_range_t, std::initializer_list<value_type>, const Compare& comp, const allocator_type&)
   multiset(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp = Compare(), const allocator_type& a = allocator_type())
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! @copydoc ::hboost::container::set::set(const set &)
   multiset(const multiset& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! @copydoc ::hboost::container::set::set(set &&)
   multiset(HBOOST_RV_REF(multiset) x)
      : base_t(HBOOST_MOVE_BASE(base_t, x))
   {}

   //! @copydoc ::hboost::container::set::set(const set &, const allocator_type &)
   multiset(const multiset& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! @copydoc ::hboost::container::set::set(set &&, const allocator_type &)
   multiset(HBOOST_RV_REF(multiset) x, const allocator_type &a)
      : base_t(HBOOST_MOVE_BASE(base_t, x), a)
   {}

   //! @copydoc ::hboost::container::set::operator=(const set &)
   multiset& operator=(HBOOST_COPY_ASSIGN_REF(multiset) x)
   {  return static_cast<multiset&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! @copydoc ::hboost::container::set::operator=(set &&)
   multiset& operator=(HBOOST_RV_REF(multiset) x)
      HBOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && hboost::container::container_detail::is_nothrow_move_assignable<Compare>::value )
   {  return static_cast<multiset&>(this->base_t::operator=(HBOOST_MOVE_BASE(base_t, x)));  }

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::hboost::container::set::operator=(std::initializer_list<value_type>)
   multiset& operator=(std::initializer_list<value_type> il)
   {
       this->clear();
       insert(il.begin(), il.end());
       return *this;
   }
#endif
   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::hboost::container::set::get_allocator()
   allocator_type get_allocator() const;

   //! @copydoc ::hboost::container::set::get_stored_allocator()
   stored_allocator_type &get_stored_allocator();

   //! @copydoc ::hboost::container::set::get_stored_allocator() const
   const stored_allocator_type &get_stored_allocator() const;

   //! @copydoc ::hboost::container::set::begin()
   iterator begin();

   //! @copydoc ::hboost::container::set::begin() const
   const_iterator begin() const;

   //! @copydoc ::hboost::container::set::cbegin() const
   const_iterator cbegin() const;

   //! @copydoc ::hboost::container::set::end()
   iterator end() HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::end() const
   const_iterator end() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::cend() const
   const_iterator cend() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::rbegin()
   reverse_iterator rbegin() HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::rbegin() const
   const_reverse_iterator rbegin() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::crbegin() const
   const_reverse_iterator crbegin() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::rend()
   reverse_iterator rend() HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::rend() const
   const_reverse_iterator rend() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::crend() const
   const_reverse_iterator crend() const HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::empty() const
   bool empty() const;

   //! @copydoc ::hboost::container::set::size() const
   size_type size() const;

   //! @copydoc ::hboost::container::set::max_size() const
   size_type max_size() const;

   #endif   //#if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   #if !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   iterator emplace(HBOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_equal(hboost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)...
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class... Args>
   iterator emplace_hint(const_iterator p, HBOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_hint_equal(p, hboost::forward<Args>(args)...); }

   #else // !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define HBOOST_CONTAINER_MULTISET_EMPLACE_CODE(N) \
   HBOOST_MOVE_TMPL_LT##N HBOOST_MOVE_CLASS##N HBOOST_MOVE_GT##N \
   iterator emplace(HBOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_equal(HBOOST_MOVE_FWD##N);  }\
   \
   HBOOST_MOVE_TMPL_LT##N HBOOST_MOVE_CLASS##N HBOOST_MOVE_GT##N \
   iterator emplace_hint(const_iterator hint HBOOST_MOVE_I##N HBOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_equal(hint HBOOST_MOVE_I##N HBOOST_MOVE_FWD##N); }\
   //
   HBOOST_MOVE_ITERATE_0TO9(HBOOST_CONTAINER_MULTISET_EMPLACE_CODE)
   #undef HBOOST_CONTAINER_MULTISET_EMPLACE_CODE

   #endif   // !defined(HBOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator insert(const value_type &x);

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(value_type &&x);
   #else
   HBOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, iterator, this->priv_insert)
   #endif

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts a value move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, value_type &&x);
   #else
   HBOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_equal(first, last);  }

#if !defined(HBOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::hboost::container::set::insert(std::initializer_list<value_type>)
   void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_equal(il.begin(), il.end());  }
#endif

   #if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::hboost::container::set::erase(const_iterator)
   iterator erase(const_iterator p);

   //! @copydoc ::hboost::container::set::erase(const key_type&)
   size_type erase(const key_type& x);

   //! @copydoc ::hboost::container::set::erase(const_iterator,const_iterator)
   iterator erase(const_iterator first, const_iterator last);

   //! @copydoc ::hboost::container::set::swap
   void swap(multiset& x)
      HBOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && hboost::container::container_detail::is_nothrow_swappable<Compare>::value );

   //! @copydoc ::hboost::container::set::clear
   void clear() HBOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::hboost::container::set::key_comp
   key_compare key_comp() const;

   //! @copydoc ::hboost::container::set::value_comp
   value_compare value_comp() const;

   //! @copydoc ::hboost::container::set::find(const key_type& )
   iterator find(const key_type& x);

   //! @copydoc ::hboost::container::set::find(const key_type& ) const
   const_iterator find(const key_type& x) const;

   //! @copydoc ::hboost::container::set::count(const key_type& ) const
   size_type count(const key_type& x) const;

   //! @copydoc ::hboost::container::set::lower_bound(const key_type& )
   iterator lower_bound(const key_type& x);

   //! @copydoc ::hboost::container::set::lower_bound(const key_type& ) const
   const_iterator lower_bound(const key_type& x) const;

   //! @copydoc ::hboost::container::set::upper_bound(const key_type& )
   iterator upper_bound(const key_type& x);

   //! @copydoc ::hboost::container::set::upper_bound(const key_type& ) const
   const_iterator upper_bound(const key_type& x) const;

   //! @copydoc ::hboost::container::set::equal_range(const key_type& ) const
   std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;

   //! @copydoc ::hboost::container::set::equal_range(const key_type& )
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! @copydoc ::hboost::container::set::rebalance()
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(multiset& x, multiset& y);

   #endif   //#if defined(HBOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   template <class KeyType>
   iterator priv_insert(HBOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_equal(::hboost::forward<KeyType>(x));  }

   template <class KeyType>
   iterator priv_insert(const_iterator p, HBOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_equal(p, ::hboost::forward<KeyType>(x)); }

   #endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class Allocator, class MultiSetOptions>
struct has_trivial_destructor_after_move<hboost::container::multiset<Key, Compare, Allocator, MultiSetOptions> >
{
   typedef typename ::hboost::container::allocator_traits<Allocator>::pointer pointer;
   static const bool value = ::hboost::has_trivial_destructor_after_move<Allocator>::value &&
                             ::hboost::has_trivial_destructor_after_move<pointer>::value &&
                             ::hboost::has_trivial_destructor_after_move<Compare>::value;
};

namespace container {

#endif   //#ifndef HBOOST_CONTAINER_DOXYGEN_INVOKED

}}

#include <hboost/container/detail/config_end.hpp>

#endif   // HBOOST_CONTAINER_SET_HPP
