///////////////////////////////////////////////////////////////////////////////
/// \file decltype.hpp
/// Contains definition the HBOOST_PROTO_DECLTYPE_() macro and assorted helpers
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HBOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008
#define HBOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008

#include <hboost/config.hpp>
#include <hboost/detail/workaround.hpp>
#include <hboost/get_pointer.hpp>
#include <hboost/preprocessor/cat.hpp>
#include <hboost/preprocessor/repetition/enum_params.hpp>
#include <hboost/preprocessor/repetition/enum_trailing_params.hpp>
#include <hboost/preprocessor/repetition/enum_binary_params.hpp>
#include <hboost/preprocessor/repetition/repeat.hpp>
#include <hboost/preprocessor/repetition/repeat_from_to.hpp>
#include <hboost/preprocessor/iteration/local.hpp>
#include <hboost/mpl/if.hpp>
#include <hboost/mpl/eval_if.hpp>
#include <hboost/mpl/identity.hpp>
#include <hboost/type_traits/is_class.hpp>
#include <hboost/type_traits/remove_reference.hpp>
#include <hboost/type_traits/is_pointer.hpp>
#include <hboost/type_traits/is_function.hpp>
#include <hboost/type_traits/is_member_object_pointer.hpp>
#include <hboost/type_traits/add_const.hpp>
#include <hboost/type_traits/add_reference.hpp>
#include <hboost/typeof/typeof.hpp>
#include <hboost/utility/addressof.hpp>
#include <hboost/utility/result_of.hpp>
#include <hboost/utility/enable_if.hpp>
#include <hboost/proto/proto_fwd.hpp>
#include <hboost/proto/detail/any.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

// We're STILL using Boost.Typeof on MSVC even for msvc-11.0 because of this bug:
// https://connect.microsoft.com/VisualStudio/feedback/details/765392/decltype-of-a-pointer-to-member-operator-gets-ref-qualification-wrong
#if !defined(HBOOST_NO_CXX11_DECLTYPE) && !HBOOST_WORKAROUND(HBOOST_MSVC, HBOOST_TESTED_AT(1700))
# define HBOOST_PROTO_DECLTYPE_(EXPR, TYPE) typedef decltype((EXPR)) TYPE;
#else
# define HBOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(NESTED, EXPR)                                     \
    HBOOST_TYPEOF_NESTED_TYPEDEF_TPL(HBOOST_PP_CAT(nested_and_hidden_, NESTED), EXPR)                 \
    static int const HBOOST_PP_CAT(sz, NESTED) = sizeof(hboost::proto::detail::check_reference(EXPR));\
    struct NESTED                                                                                   \
      : hboost::mpl::if_c<                                                                           \
            1 == HBOOST_PP_CAT(sz, NESTED)                                                           \
          , typename HBOOST_PP_CAT(nested_and_hidden_, NESTED)::type &                               \
          , typename HBOOST_PP_CAT(nested_and_hidden_, NESTED)::type                                 \
        >                                                                                           \
    {};
# define HBOOST_PROTO_DECLTYPE_(EXPR, TYPE)                                                          \
    HBOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(HBOOST_PP_CAT(nested_, TYPE), (EXPR))                   \
    typedef typename HBOOST_PP_CAT(nested_, TYPE)::type TYPE;
#endif

namespace hboost { namespace proto
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct as_mutable
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T &>
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T const &>
        {
            typedef T &type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T make();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        typename as_mutable<T>::type make_mutable();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct subscript_wrapper
          : T
        {
            using T::operator[];

            #if HBOOST_WORKAROUND(HBOOST_MSVC, HBOOST_TESTED_AT(1500))
            any operator[](any const volatile &) const volatile;
            #else
            any operator[](any const &) const volatile;
            #endif
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct as_subscriptable
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T>
                  , T
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T const>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> const
                  , T const
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T &>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> &
                  , T &
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T const &>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> const &
                  , T const &
                >::type
            type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        typename as_subscriptable<T>::type make_subscriptable();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        char check_reference(T &);

        template<typename T>
        char (&check_reference(T const &))[2];

        namespace has_get_pointerns
        {
            using hboost::get_pointer;
            void *(&get_pointer(...))[2];

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<typename T>
            struct has_get_pointer
            {
                static const bool value = sizeof(void *) == sizeof(get_pointer(make<T &>()));
                typedef mpl::bool_<value> type;
            };
        }

        using has_get_pointerns::has_get_pointer;

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct class_member_traits;

        template<typename T, typename U>
        struct class_member_traits<T U::*>
        {
            typedef U class_type;
            typedef T result_type;
        };

        // Other specializations are generated by the preprocessor
        #include <hboost/proto/detail/class_member_traits.hpp>

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T &lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        T const &lvalue(T const &t)
        {
            return t;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename U, typename V, typename T>
        U *proto_get_pointer(T &t, V *, U *)
        {
            return hboost::addressof(t);
        }

        template<typename U, typename V, typename T>
        U const *proto_get_pointer(T &t, V *, U const *)
        {
            return hboost::addressof(t);
        }

        template<typename U, typename V, typename T>
        V *proto_get_pointer(T &t, V *, ...)
        {
            return get_pointer(t);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        #define HBOOST_PROTO_USE_GET_POINTER()                                                       \
        using namespace hboost::proto::detail::get_pointerns                                         \
        /**/

        #define HBOOST_PROTO_GET_POINTER(Type, Obj)                                                  \
        hboost::proto::detail::proto_get_pointer<Type>(                                              \
            hboost::proto::detail::lvalue(Obj)                                                       \
          , (true ? 0 : get_pointer(Obj))                                                           \
          , (true ? 0 : hboost::addressof(hboost::proto::detail::lvalue(Obj)))                        \
        )                                                                                           \
        /**/

        ////////////////////////////////////////////////////////////////////////////////////////////
        namespace get_pointerns
        {
            using hboost::get_pointer;

            template<typename T>
            typename disable_if_c<has_get_pointer<T>::value, T *>::type
            get_pointer(T &t)
            {
                return hboost::addressof(t);
            }

            template<typename T>
            typename disable_if_c<has_get_pointer<T>::value, T const *>::type
            get_pointer(T const &t)
            {
                return hboost::addressof(t);
            }

            char test_ptr_to_const(void *);
            char (&test_ptr_to_const(void const *))[2];

            template<typename U> char test_V_is_a_U(U *);
            template<typename U> char test_V_is_a_U(U const *);
            template<typename U> char (&test_V_is_a_U(...))[2];

            ////////////////////////////////////////////////////////////////////////////////////////////
            // result_of_ is a wrapper around hboost::result_of that also handles "invocations" of
            // member object pointers.
            template<typename T, typename Void = void>
            struct result_of_
              : HBOOST_PROTO_RESULT_OF<T>
            {};

            template<typename T, typename U, typename V>
            struct result_of_<T U::*(V), typename enable_if_c<is_member_object_pointer<T U::*>::value>::type>
            {
                static const bool is_V_a_smart_ptr = 2 == sizeof(test_V_is_a_U<U>(&lvalue(make<V>())));
                static const bool is_ptr_to_const = 2 == sizeof(test_ptr_to_const(HBOOST_PROTO_GET_POINTER(U, make<V>())));

                // If V is not a U, then it is a (smart) pointer and we can always return an lvalue.
                // Otherwise, we can only return an lvalue if we are given one.
                typedef
                    typename mpl::eval_if_c<
                        (is_V_a_smart_ptr || is_reference<V>::value)
                      , mpl::eval_if_c<
                            is_ptr_to_const
                          , add_reference<typename add_const<T>::type>
                          , add_reference<T>
                        >
                      , mpl::identity<T>
                    >::type
                type;
            };

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<
                typename T
              , typename U
              , bool IsMemPtr = is_member_object_pointer<
                    typename remove_reference<U>::type
                >::value
            >
            struct mem_ptr_fun
            {
                HBOOST_PROTO_DECLTYPE_(
                    proto::detail::make_mutable<T>() ->* proto::detail::make<U>()
                  , result_type
                )

                result_type operator()(
                    typename add_reference<typename add_const<T>::type>::type t
                  , typename add_reference<typename add_const<U>::type>::type u
                ) const
                {
                    return t ->* u;
                }
            };

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<typename T, typename U>
            struct mem_ptr_fun<T, U, true>
            {
                typedef
                    typename class_member_traits<
                        typename uncvref<U>::type
                    >::class_type
                V;

                HBOOST_PROTO_DECLTYPE_(
                    HBOOST_PROTO_GET_POINTER(V, proto::detail::make_mutable<T>()) ->* proto::detail::make<U>()
                  , result_type
                )

                result_type operator()(
                    typename add_reference<typename add_const<T>::type>::type t
                  , U u
                ) const
                {
                    return HBOOST_PROTO_GET_POINTER(V, t) ->* u;
                }
            };
        }

        using get_pointerns::result_of_;
        using get_pointerns::mem_ptr_fun;

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename A0, typename A1>
        struct comma_result
        {
            HBOOST_PROTO_DECLTYPE_((proto::detail::make<A0>(), proto::detail::make<A1>()), type)
        };

        template<typename A0>
        struct comma_result<A0, void>
        {
            typedef void type;
        };

        template<typename A1>
        struct comma_result<void, A1>
        {
            typedef A1 type;
        };

        template<>
        struct comma_result<void, void>
        {
            typedef void type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        // normalize a function type for use with hboost::result_of
        template<typename T, typename U = T>
        struct result_of_fixup
          : mpl::if_c<is_function<T>::value, T *, U>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T const &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T *, U>
          : result_of_fixup<T, U>
        {};

        template<typename R, typename T, typename U>
        struct result_of_fixup<R T::*, U>
        {
            typedef R T::*type;
        };

        template<typename T, typename U>
        struct result_of_fixup<T const, U>
          : result_of_fixup<T, U>
        {};

        //// Tests for result_of_fixup
        //struct bar {};
        //HBOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar>::type>));
        //HBOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const>::type>));
        //HBOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar &>::type>));
        //HBOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const &>::type>));
        //HBOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(*)()>::type>));
        //HBOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const)()>::type>));
        //HBOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const &)()>::type>));
        //HBOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(&)()>::type>));

        template<typename T, typename PMF>
        struct memfun
        {
            typedef typename uncvref<PMF>::type pmf_type;
            typedef typename class_member_traits<pmf_type>::class_type V;
            typedef typename class_member_traits<pmf_type>::result_type result_type;

            memfun(T t, pmf_type p)
              : obj(t)
              , pmf(p)
            {}

            result_type operator()() const
            {
                HBOOST_PROTO_USE_GET_POINTER();
                return (HBOOST_PROTO_GET_POINTER(V, obj) ->* pmf)();
            }

            // Other overloads generated by the preprocessor
            #include <hboost/proto/detail/memfun_funop.hpp>

        private:
            T obj;
            pmf_type pmf;
        };

    } // namespace detail
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif
