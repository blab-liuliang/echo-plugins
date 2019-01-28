// Copyright (C) 2005 Arkadiy Vertleyb, Peder Holt.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef HBOOST_TYPEOF_STD_map_hpp_INCLUDED
#define HBOOST_TYPEOF_STD_map_hpp_INCLUDED

#include <map>
#include <hboost/typeof/typeof.hpp>
#include <hboost/typeof/std/memory.hpp>
#include <hboost/typeof/std/functional.hpp>
#include <hboost/typeof/std/utility.hpp>

#include HBOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

HBOOST_TYPEOF_REGISTER_TEMPLATE(std::map, 2)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::map, 3)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::map, 4)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::multimap, 2)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::multimap, 3)
HBOOST_TYPEOF_REGISTER_TEMPLATE(std::multimap, 4)

#endif//HBOOST_TYPEOF_STD_map_hpp_INCLUDED
