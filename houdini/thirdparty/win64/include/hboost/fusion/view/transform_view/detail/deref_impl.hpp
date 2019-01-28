/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(HBOOST_FUSION_DEREF_IMPL_07162005_1026)
#define HBOOST_FUSION_DEREF_IMPL_07162005_1026

#include <hboost/fusion/support/config.hpp>
#include <hboost/mpl/apply.hpp>
#include <hboost/fusion/iterator/deref.hpp>
#include <hboost/fusion/iterator/value_of.hpp>
#include <hboost/fusion/view/transform_view/detail/apply_transform_result.hpp>

namespace hboost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        // Unary Version
        template <>
        struct deref_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef detail::apply_transform_result<typename Iterator::transform_type> transform_type;
                typedef typename mpl::apply<transform_type, value_type>::type type;

                HBOOST_CONSTEXPR HBOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }
            };
        };

        // Binary Version
        template <>
        struct deref_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::deref<typename Iterator::first2_type>::type
                value2_type;

                typedef detail::apply_transform_result<typename Iterator::transform_type> transform_type;
                typedef typename mpl::apply<transform_type, value1_type, value2_type>::type type;

                HBOOST_CONSTEXPR HBOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }
            };
        };    
    }
}}

#endif


