//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef HBOOST_RANGE_ALGORITHM_PARTIAL_SORT_HPP_INCLUDED
#define HBOOST_RANGE_ALGORITHM_PARTIAL_SORT_HPP_INCLUDED

#include <hboost/concept_check.hpp>
#include <hboost/range/begin.hpp>
#include <hboost/range/end.hpp>
#include <hboost/range/concepts.hpp>
#include <algorithm>

namespace hboost
{
    namespace range
    {

/// \brief template function partial_sort
///
/// range-based version of the partial_sort std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class RandomAccessRange>
inline RandomAccessRange& partial_sort(RandomAccessRange& rng,
    HBOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type middle)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::partial_sort(hboost::begin(rng), middle, hboost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& partial_sort(const RandomAccessRange& rng,
    HBOOST_DEDUCED_TYPENAME range_iterator<const RandomAccessRange>::type middle)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::partial_sort(hboost::begin(rng), middle, hboost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class BinaryPredicate>
inline RandomAccessRange& partial_sort(RandomAccessRange& rng,
    HBOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type middle,
    BinaryPredicate sort_pred)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::partial_sort(hboost::begin(rng), middle, hboost::end(rng),
                        sort_pred);
    return rng;
}

/// \overload
template<class RandomAccessRange, class BinaryPredicate>
inline const RandomAccessRange& partial_sort(const RandomAccessRange& rng,
    HBOOST_DEDUCED_TYPENAME range_iterator<const RandomAccessRange>::type middle,
    BinaryPredicate sort_pred)
{
    HBOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::partial_sort(hboost::begin(rng), middle, hboost::end(rng),
                        sort_pred);
    return rng;
}

    } // namespace range
    using range::partial_sort;
} // namespace hboost

#endif // include guard
