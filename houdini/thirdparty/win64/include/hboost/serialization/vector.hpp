#ifndef  HBOOST_SERIALIZATION_VECTOR_HPP
#define HBOOST_SERIALIZATION_VECTOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector.hpp: serialization for stl vector templates

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// fast array serialization (C) Copyright 2005 Matthias Troyer 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <vector>

#include <hboost/config.hpp>
#include <hboost/detail/workaround.hpp>

#include <hboost/archive/detail/basic_iarchive.hpp>
#include <hboost/serialization/access.hpp>
#include <hboost/serialization/nvp.hpp>
#include <hboost/serialization/collection_size_type.hpp>
#include <hboost/serialization/item_version_type.hpp>

#include <hboost/serialization/collections_save_imp.hpp>
#include <hboost/serialization/collections_load_imp.hpp>
#include <hboost/serialization/split_free.hpp>
#include <hboost/serialization/array.hpp>
#include <hboost/serialization/detail/get_data.hpp>
#include <hboost/serialization/detail/stack_constructor.hpp>
#include <hboost/mpl/bool_fwd.hpp>
#include <hboost/mpl/if.hpp>

// default is being compatible with version 1.34.1 files, not 1.35 files
#ifndef HBOOST_SERIALIZATION_VECTOR_VERSIONED
#define HBOOST_SERIALIZATION_VECTOR_VERSIONED(V) (V==4 || V==5)
#endif

// function specializations must be defined in the appropriate
// namespace - hboost::serialization
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define STD _STLP_STD
#else
#define STD std
#endif

namespace hboost { 
namespace serialization {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector< T >

// the default versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    hboost::serialization::stl::save_collection<Archive, STD::vector<U, Allocator> >(
        ar, t
    );
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    const hboost::archive::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    item_version_type item_version(0);
    collection_size_type count;
    ar >> HBOOST_SERIALIZATION_NVP(count);
    if(hboost::archive::library_version_type(3) < library_version){
        ar >> HBOOST_SERIALIZATION_NVP(item_version);
    }
    t.reserve(count);
    stl::collection_load_impl(ar, t, count, item_version);
}

// the optimized versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    const collection_size_type count(t.size());
    ar << HBOOST_SERIALIZATION_NVP(count);
    if (!t.empty())
        ar << hboost::serialization::make_array(detail::get_data(t),t.size());
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::true_
){
    collection_size_type count(t.size());
    ar >> HBOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    unsigned int item_version=0;
    if(HBOOST_SERIALIZATION_VECTOR_VERSIONED(ar.get_library_version())) {
        ar >> HBOOST_SERIALIZATION_NVP(item_version);
    }
    if (!t.empty())
        ar >> hboost::serialization::make_array(detail::get_data(t),t.size());
  }

// dispatch to either default or optimized versions

template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int file_version
){
    typedef typename 
    hboost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type 
    >::type use_optimized;
    save(ar,t,file_version, use_optimized());
}

template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int file_version
){
#ifdef HBOOST_SERIALIZATION_VECTOR_135_HPP
    if (ar.get_library_version()==hboost::archive::library_version_type(5))
    {
      load(ar,t,file_version, hboost::is_arithmetic<U>());
      return;
    }
#endif
    typedef typename 
    hboost::serialization::use_array_optimization<Archive>::template apply<
        typename remove_const<U>::type 
    >::type use_optimized;
    load(ar,t,file_version, use_optimized());
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::vector<U, Allocator> & t,
    const unsigned int file_version
){
    hboost::serialization::split_free(ar, t, file_version);
}

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// vector<bool>
template<class Archive, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // record number of elements
    collection_size_type count (t.size());
    ar << HBOOST_SERIALIZATION_NVP(count);
    std::vector<bool>::const_iterator it = t.begin();
    while(count-- > 0){
        bool tb = *it++;
        ar << hboost::serialization::make_nvp("item", tb);
    }
}

template<class Archive, class Allocator>
inline void load(
    Archive & ar,
    std::vector<bool, Allocator> &t,
    const unsigned int /* file_version */
){
    // retrieve number of elements
    collection_size_type count;
    ar >> HBOOST_SERIALIZATION_NVP(count);
    t.resize(count);
    for(collection_size_type i = collection_size_type(0); i < count; ++i){
        bool b;
        ar >> hboost::serialization::make_nvp("item", b);
        t[i] = b;
    }
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Allocator>
inline void serialize(
    Archive & ar,
    std::vector<bool, Allocator> & t,
    const unsigned int file_version
){
    hboost::serialization::split_free(ar, t, file_version);
}

} // serialization
} // namespace hboost

#include <hboost/serialization/collection_traits.hpp>

HBOOST_SERIALIZATION_COLLECTION_TRAITS(std::vector)
#undef STD

#endif // HBOOST_SERIALIZATION_VECTOR_HPP
