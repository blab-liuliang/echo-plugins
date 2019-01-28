// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef HBOOST_RANGE_ADAPTOR_MAP_HPP
#define HBOOST_RANGE_ADAPTOR_MAP_HPP

#include <hboost/range/adaptor/transformed.hpp>
#include <hboost/range/iterator_range.hpp>
#include <hboost/range/value_type.hpp>
#include <hboost/range/reference.hpp>
#include <hboost/range/concepts.hpp>

namespace hboost
{
    namespace range_detail
    {
        struct map_keys_forwarder {};
        struct map_values_forwarder {};

        template< class Map >
        struct select_first
        {
            typedef HBOOST_DEDUCED_TYPENAME range_reference<const Map>::type argument_type;
            typedef const HBOOST_DEDUCED_TYPENAME range_value<const Map>::type::first_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.first;
            }
        };

        template< class Map >
        struct select_second_mutable
        {
            typedef HBOOST_DEDUCED_TYPENAME range_reference<Map>::type argument_type;
            typedef HBOOST_DEDUCED_TYPENAME range_value<Map>::type::second_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.second;
            }
        };

        template< class Map >
        struct select_second_const
        {
            typedef HBOOST_DEDUCED_TYPENAME range_reference<const Map>::type argument_type;
            typedef const HBOOST_DEDUCED_TYPENAME range_value<const Map>::type::second_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.second;
            }
        };

        template<class StdPairRng>
        class select_first_range
            : public transformed_range<
                        select_first<StdPairRng>,
                        const StdPairRng>
        {
            typedef transformed_range<select_first<StdPairRng>, const StdPairRng> base;
        public:
            typedef select_first<StdPairRng> transform_fn_type;
            typedef const StdPairRng source_range_type;

            select_first_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_first_range(const base& other) : base(other) {}
        };

        template<class StdPairRng>
        class select_second_mutable_range
            : public transformed_range<
                        select_second_mutable<StdPairRng>,
                        StdPairRng>
        {
            typedef transformed_range<select_second_mutable<StdPairRng>, StdPairRng> base;
        public:
            typedef select_second_mutable<StdPairRng> transform_fn_type;
            typedef StdPairRng source_range_type;

            select_second_mutable_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_second_mutable_range(const base& other) : base(other) {}
        };

        template<class StdPairRng>
        class select_second_const_range
            : public transformed_range<
                        select_second_const<StdPairRng>,
                        const StdPairRng>
        {
            typedef transformed_range<select_second_const<StdPairRng>, const StdPairRng> base;
        public:
            typedef select_second_const<StdPairRng> transform_fn_type;
            typedef const StdPairRng source_range_type;

            select_second_const_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_second_const_range(const base& other) : base(other) {}
        };

        template< class StdPairRng >
        inline select_first_range<StdPairRng>
        operator|( const StdPairRng& r, map_keys_forwarder )
        {
            HBOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRng>));

            return operator|( r,
                hboost::adaptors::transformed( select_first<StdPairRng>() ) );
        }

        template< class StdPairRng >
        inline select_second_mutable_range<StdPairRng>
        operator|( StdPairRng& r, map_values_forwarder )
        {
            HBOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<StdPairRng>));

            return operator|( r,
                hboost::adaptors::transformed( select_second_mutable<StdPairRng>() ) );
        }

        template< class StdPairRng >
        inline select_second_const_range<StdPairRng>
        operator|( const StdPairRng& r, map_values_forwarder )
        {
            HBOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRng>));

            return operator|( r,
                hboost::adaptors::transformed( select_second_const<StdPairRng>() ) );
        }

    } // 'range_detail'

    using range_detail::select_first_range;
    using range_detail::select_second_mutable_range;
    using range_detail::select_second_const_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::map_keys_forwarder map_keys =
                                            range_detail::map_keys_forwarder();

            const range_detail::map_values_forwarder map_values =
                                           range_detail::map_values_forwarder();
        }

        template<class StdPairRange>
        inline select_first_range<StdPairRange>
        keys(const StdPairRange& rng)
        {
            HBOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRange>));

            return select_first_range<StdPairRange>(
                range_detail::select_first<StdPairRange>(), rng );
        }

        template<class StdPairRange>
        inline select_second_const_range<StdPairRange>
        values(const StdPairRange& rng)
        {
            HBOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRange>));

            return select_second_const_range<StdPairRange>(
                range_detail::select_second_const<StdPairRange>(), rng );
        }

        template<class StdPairRange>
        inline select_second_mutable_range<StdPairRange>
        values(StdPairRange& rng)
        {
            HBOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<StdPairRange>));

            return select_second_mutable_range<StdPairRange>(
                range_detail::select_second_mutable<StdPairRange>(), rng );
        }
    } // 'adaptors'

}

#endif
