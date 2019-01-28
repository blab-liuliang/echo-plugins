// Copyright (C) 2005 Arkadiy Vertleyb, Peder Holt.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef HBOOST_TYPEOF_STD_valarray_hpp_INCLUDED
#define HBOOST_TYPEOF_STD_valarray_hpp_INCLUDED

#include <valarray>
#include <hboost/typeof/typeof.hpp>

#include HBOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

HBOOST_TYPEOF_REGISTER_TEMPLATE(std::valarray, 1)
HBOOST_TYPEOF_REGISTER_TYPE(std::slice)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::slice_array, 1)
HBOOST_TYPEOF_REGISTER_TYPE(std::gslice)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::gslice_array, 1)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::mask_array, 1)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::indirect_array, 1)

#endif//HBOOST_TYPEOF_STD_valarray_hpp_INCLUDED
