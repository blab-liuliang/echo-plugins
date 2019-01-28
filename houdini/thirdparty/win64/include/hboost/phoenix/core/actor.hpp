/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2014 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef HBOOST_PHOENIX_CORE_ACTOR_HPP
#define HBOOST_PHOENIX_CORE_ACTOR_HPP

#include <hboost/phoenix/core/limits.hpp>

#include <hboost/is_placeholder.hpp>
#include <hboost/mpl/identity.hpp>
#include <hboost/mpl/eval_if.hpp>
#include <hboost/phoenix/core/domain.hpp>
#include <hboost/phoenix/core/environment.hpp>
#include <hboost/phoenix/core/is_nullary.hpp>
#include <hboost/phoenix/core/meta_grammar.hpp>
#include <hboost/phoenix/support/iterate.hpp>
#include <hboost/phoenix/support/vector.hpp>
#include <hboost/proto/extends.hpp>
#include <hboost/proto/make_expr.hpp>
#include <hboost/utility/result_of.hpp>
#include <hboost/mpl/void.hpp>
#include <cstring>

#ifdef HBOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4522) // 'this' used in base member initializer list
#pragma warning(disable: 4510) // default constructor could not be generated
#pragma warning(disable: 4610) // can never be instantiated - user defined cons
#endif

namespace hboost { namespace hboostphoenix
{
    template <typename Expr>
    struct actor;

    namespace detail
    {
        struct error_expecting_arguments
        {
            template <typename T>
            error_expecting_arguments(T const&) {}
        };
        
        struct error_invalid_lambda_expr
        {
            template <typename T>
            error_invalid_lambda_expr(T const&) {}
        };

        template <typename T>
        struct result_type_deduction_helper
        {
            typedef T const & type;
        };

        template <typename T>
        struct result_type_deduction_helper<T &>
        {
            typedef T & type;
        };

        template <typename T>
        struct result_type_deduction_helper<T const &>
        {
            typedef T const & type;
        };

        struct do_assign
        {
            HBOOST_PROTO_CALLABLE()

            typedef void result_type;

            template <typename T1, typename T2>
            void operator()(T1 & t1, T2 const & t2) const
            {
                proto::value(t1) = proto::value(t2);
            }
        };

    #define HBOOST_PHOENIX_ACTOR_ASSIGN_CHILD(N)                                 \
        assign(                                                                 \
            proto::_child_c<N>                                                  \
          , proto::call<                                                        \
                proto::_child_c<N>(proto::_state)                               \
            >                                                                   \
        )                                                                       \
    /**/
    #define HBOOST_PHOENIX_ACTOR_START_ASSIGN_CHILD(Z, N, D)                     \
       proto::and_<                                                             \
            HBOOST_PHOENIX_ACTOR_ASSIGN_CHILD(N)                                 \
    /**/
    #define HBOOST_PHOENIX_ACTOR_END_ASSIGN(Z, N, D)                             \
        >                                                                       \
    /**/
    #define HBOOST_PHOENIX_ACTOR_ASSIGN_CALL(N)                                  \
           proto::when<                                                        \
                proto::nary_expr<proto::_ ,                                     \
                  HBOOST_PP_ENUM_PARAMS(N, proto::_ HBOOST_PP_INTERCEPT)          \
                >                                                               \
                , HBOOST_PP_ENUM(                                                 \
                     N                                                          \
                  , HBOOST_PHOENIX_ACTOR_START_ASSIGN_CHILD                     \
                  , _                                                          \
                 )                                                              \
                 HBOOST_PP_REPEAT(                                               \
                     N                                                          \
                   , HBOOST_PHOENIX_ACTOR_END_ASSIGN                             \
                   , _                                                          \
                 )                                                              \
            >                                                                   \
      /**/
    #define HBOOST_PHOENIX_ACTOR_START_ASSIGN_CALL(Z, N, D)                      \
        proto::or_<                                                             \
            HBOOST_PHOENIX_ACTOR_ASSIGN_CALL(N)                                  \
    /**/
 
#if !defined(HBOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#include <hboost/phoenix/core/preprocessed/actor.hpp>
#else
#if defined(__WAVE__) && defined(HBOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_" HBOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(HBOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

        struct assign
            : HBOOST_PP_ENUM_SHIFTED(
                  HBOOST_PHOENIX_LIMIT
                , HBOOST_PHOENIX_ACTOR_START_ASSIGN_CALL
                , _
              )
              , proto::when<
                    proto::terminal<proto::_>
                  , do_assign(proto::_, proto::_state)
                >
              HBOOST_PP_REPEAT(
                  HBOOST_PP_DEC(HBOOST_PHOENIX_LIMIT)
                , HBOOST_PHOENIX_ACTOR_END_ASSIGN
                , _
              )
        {};

#if defined(__WAVE__) && defined(HBOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif
    #undef HBOOST_PHOENIX_ACTOR_ASSIGN_CALL
    #undef HBOOST_PHOENIX_ACTOR_START_ASSIGN_CALL
    #undef HBOOST_PHOENIX_ACTOR_END_ASSIGN_CALL
    #undef HBOOST_PHOENIX_ACTOR_ASSIGN_CHILD
    #undef HBOOST_PHOENIX_ACTOR_START_ASSIGN_CHILD
    #undef HBOOST_PHOENIX_ACTOR_END_ASSIGN_CHILD
    }

    // Bring in the result_of::actor<>
    #include <hboost/phoenix/core/detail/actor_result_of.hpp>

    ////////////////////////////////////////////////////////////////////////////
    //
    //  actor
    //
    //      The actor class. The main thing! In phoenix, everything is an actor
    //      This class is responsible for full function evaluation. Partial
    //      function evaluation involves creating a hierarchy of actor objects.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct actor
    {
        typedef typename
            mpl::eval_if_c<
                mpl::or_<
                    is_custom_terminal<Expr>
                  , mpl::bool_<is_placeholder<Expr>::value>
                >::value
              , proto::terminal<Expr>
              , mpl::identity<Expr>
            >::type
            expr_type;
        
        HBOOST_PROTO_BASIC_EXTENDS(expr_type, actor<expr_type>, phoenix_domain)

        // providing operator= to be assignable
        actor& operator=(actor const& other)
        {
            detail::assign()(*this, other);
            return *this;
        }
        actor& operator=(actor & other)
        {
            detail::assign()(*this, other);
            return *this;
        }

        template <typename A0>
        typename proto::result_of::make_expr<
            proto::tag::assign
          , phoenix_domain
          , proto_base_expr
          , A0
        >::type const
        operator=(A0 const & a0) const
        {
            return proto::make_expr<proto::tag::assign, phoenix_domain>(this->proto_expr_, a0);
        }

        template <typename A0>
        typename proto::result_of::make_expr<
            proto::tag::assign
          , phoenix_domain
          , proto_base_expr
          , A0
        >::type const
        operator=(A0 & a0) const
        {
            return proto::make_expr<proto::tag::assign, phoenix_domain>(this->proto_expr_, a0);
        }
        
        template <typename A0>
        typename proto::result_of::make_expr<
            proto::tag::subscript
          , phoenix_domain
          , proto_base_expr
          , A0
        >::type const
        operator[](A0 const & a0) const
        {
            return proto::make_expr<proto::tag::subscript, phoenix_domain>(this->proto_expr_, a0);
        }

        template <typename A0>
        typename proto::result_of::make_expr<
            proto::tag::subscript
          , phoenix_domain
          , proto_base_expr
          , A0
        >::type const
        operator[](A0 & a0) const
        {
            return proto::make_expr<proto::tag::subscript, phoenix_domain>(this->proto_expr_, a0);
        }

        template <typename Sig>
        struct result;

        typename result_of::actor<proto_base_expr>::type
        operator()()
        {
            typedef vector1<const actor<Expr> *> env_type;
            env_type env = {this};
            
            return hboostphoenix::eval(*this, hboostphoenix::context(env, default_actions()));
        }

        typename result_of::actor<proto_base_expr>::type
        operator()() const
        {
            typedef vector1<const actor<Expr> *> env_type;
            env_type env = {this};
            
            return hboostphoenix::eval(*this, hboostphoenix::context(env, default_actions()));
        }

        template <typename Env>
        typename evaluator::impl<
            proto_base_expr const &
          , typename result_of::context<
                Env const &
              , default_actions const &
            >::type
          , proto::empty_env
        >::result_type
        eval(Env const & env) const
        {
            return hboostphoenix::eval(*this, hboostphoenix::context(env, default_actions()));
        }
        
        // Bring in the rest
        #include <hboost/phoenix/core/detail/actor_operator.hpp>
    };

}}

namespace hboost
{
    // specialize hboost::result_of to return the proper result type
    template <typename Expr>
    struct result_of<hboostphoenix::actor<Expr>()>
        : hboostphoenix::result_of::actor<typename hboostphoenix::actor<Expr>::proto_base_expr>
    {};
    
    template <typename Expr>
    struct result_of<hboostphoenix::actor<Expr> const()>
        : hboostphoenix::result_of::actor<typename hboostphoenix::actor<Expr>::proto_base_expr>
    {};
}


#ifdef HBOOST_MSVC
#pragma warning(pop)
#endif

#endif

