//  get_current_process.hpp  --------------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba
//  Copyright 2015 Andrey Semashev

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef HBOOST_DETAIL_WINAPI_GET_CURRENT_PROCESS_HPP
#define HBOOST_DETAIL_WINAPI_GET_CURRENT_PROCESS_HPP

#include <hboost/detail/winapi/basic_types.hpp>

#ifdef HBOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Windows CE define GetCurrentProcess as an inline function in kfuncs.h
#if !defined( HBOOST_USE_WINDOWS_H ) && !defined( UNDER_CE )
extern "C" {
HBOOST_SYMBOL_IMPORT hboost::detail::winapi::HANDLE_ WINAPI GetCurrentProcess(HBOOST_DETAIL_WINAPI_VOID);
}
#endif

namespace hboost {
namespace detail {
namespace winapi {
using ::GetCurrentProcess;
}
}
}

#endif // HBOOST_DETAIL_WINAPI_GET_CURRENT_PROCESS_HPP
