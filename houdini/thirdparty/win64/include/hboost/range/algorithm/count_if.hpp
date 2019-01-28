//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef HBOOST_RANGE_ALGORITHM_COUNT_IF_HPP_INCLUDED
#define HBOOST_RANGE_ALGORITHM_COUNT_IF_HPP_INCLUDED

#include <hboost/concept_check.hpp>
#include <hboost/range/begin.hpp>
#include <hboost/range/end.hpp>
#include <hboost/range/concepts.hpp>
#include <hboost/range/difference_type.hpp>
#include <algorithm>

namespace hboost
{
    namespace range
    {

/// \brief template function count_if
///
/// range-based version of the count_if std algorithm
///
/// \pre SinglePassRange is a model of the SinglePassRangeConcept
/// \pre UnaryPredicate is a model of the UnaryPredicateConcept
template< class SinglePassRange, class UnaryPredicate >
inline HBOOST_DEDUCED_TYPENAME hboost::range_difference<SinglePassRange>::type
count_if(SinglePassRange& rng, UnaryPredicate pred)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
    return std::count_if(hboost::begin(rng), hboost::end(rng), pred);
}

/// \overload
template< class SinglePassRange, class UnaryPredicate >
inline HBOOST_DEDUCED_TYPENAME hboost::range_difference<const SinglePassRange>::type
count_if(const SinglePassRange& rng, UnaryPredicate pred)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    return std::count_if(hboost::begin(rng), hboost::end(rng), pred);
}

    } // namespace range
    using range::count_if;
} // namespace hboost

#endif // include guard
