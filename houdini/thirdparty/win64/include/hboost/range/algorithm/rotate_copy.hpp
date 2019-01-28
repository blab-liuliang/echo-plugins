//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef HBOOST_RANGE_ALGORITHM_ROTATE_COPY_HPP_INCLUDED
#define HBOOST_RANGE_ALGORITHM_ROTATE_COPY_HPP_INCLUDED

#include <hboost/concept_check.hpp>
#include <hboost/range/begin.hpp>
#include <hboost/range/end.hpp>
#include <hboost/range/concepts.hpp>
#include <hboost/range/iterator.hpp>
#include <algorithm>

namespace hboost
{
    namespace range
    {

    /// \brief template function rotate
    ///
    /// range-based version of the rotate std algorithm
    ///
    /// \pre Rng meets the requirements for a Forward range
    template<typename ForwardRange, typename OutputIterator>
    inline OutputIterator rotate_copy(
        const ForwardRange&                                             rng,
        HBOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type middle,
        OutputIterator                                                  target
        )
    {
        HBOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
        return std::rotate_copy(hboost::begin(rng), middle, hboost::end(rng), target);
    }

    } // namespace range
    using range::rotate_copy;
} // namespace hboost

#endif // include guard
