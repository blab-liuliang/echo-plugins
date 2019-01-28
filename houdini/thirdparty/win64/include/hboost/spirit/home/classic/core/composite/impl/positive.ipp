/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(HBOOST_SPIRIT_POSITIVE_IPP)
#define HBOOST_SPIRIT_POSITIVE_IPP

namespace hboost { namespace spirit {

HBOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  positive class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S>
    inline positive<S>
    operator+(parser<S> const& a)
    {
        return positive<S>(a.derived());
    }

HBOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace hboost::spirit

#endif
