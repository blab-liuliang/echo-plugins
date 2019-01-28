/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef HBOOST_PP_IS_ITERATING
#if !defined(HBOOST_FUSION_MAKE_VECTOR_07162005_0243)
#define HBOOST_FUSION_MAKE_VECTOR_07162005_0243

#include <hboost/preprocessor/iterate.hpp>
#include <hboost/preprocessor/repetition/enum_params.hpp>
#include <hboost/preprocessor/repetition/enum_binary_params.hpp>
#include <hboost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <hboost/preprocessor/repetition/repeat_from_to.hpp>
#include <hboost/fusion/container/vector/vector.hpp>
#include <hboost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(HBOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <hboost/fusion/container/generation/detail/preprocessed/make_vector.hpp>
#else
#if defined(__WAVE__) && defined(HBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_vector" FUSION_MAX_VECTOR_SIZE_STR".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(HBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace hboost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <
            HBOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_vector;

        template <>
        struct make_vector<>
        {
            typedef vector0<> type;
        };
    }

    HBOOST_CONSTEXPR HBOOST_FUSION_GPU_ENABLED
    inline vector0<>
    make_vector()
    {
        return vector0<>();
    }

#define HBOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<HBOOST_PP_CAT(T, n)>::type

#define HBOOST_PP_FILENAME_1 <hboost/fusion/container/generation/detail/pp_make_vector.hpp>
#define HBOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include HBOOST_PP_ITERATE()

#undef HBOOST_FUSION_AS_FUSION_ELEMENT

}}

#if defined(__WAVE__) && defined(HBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // HBOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(HBOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N HBOOST_PP_ITERATION()

    namespace result_of
    {
        template <HBOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct make_vector< HBOOST_PP_ENUM_PARAMS(N, T) HBOOST_PP_REPEAT_FROM_TO(HBOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef HBOOST_PP_CAT(vector, N)<HBOOST_PP_ENUM(N, HBOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <HBOOST_PP_ENUM_PARAMS(N, typename T)>
    HBOOST_CONSTEXPR HBOOST_FUSION_GPU_ENABLED
    inline HBOOST_PP_CAT(vector, N)<HBOOST_PP_ENUM(N, HBOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_vector(HBOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return HBOOST_PP_CAT(vector, N)<HBOOST_PP_ENUM(N, HBOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            HBOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(HBOOST_PP_IS_ITERATING)

