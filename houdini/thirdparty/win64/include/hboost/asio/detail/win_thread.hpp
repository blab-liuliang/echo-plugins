//
// detail/win_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HBOOST_ASIO_DETAIL_WIN_THREAD_HPP
#define HBOOST_ASIO_DETAIL_WIN_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <hboost/asio/detail/config.hpp>

#if defined(HBOOST_ASIO_WINDOWS) \
  && !defined(HBOOST_ASIO_WINDOWS_APP) \
  && !defined(UNDER_CE)

#include <hboost/asio/detail/noncopyable.hpp>
#include <hboost/asio/detail/socket_types.hpp>

#include <hboost/asio/detail/push_options.hpp>

namespace hboost {
namespace asio {
namespace detail {

HBOOST_ASIO_DECL unsigned int __stdcall win_thread_function(void* arg);

#if defined(WINVER) && (WINVER < 0x0500)
HBOOST_ASIO_DECL void __stdcall apc_function(ULONG data);
#else
HBOOST_ASIO_DECL void __stdcall apc_function(ULONG_PTR data);
#endif

template <typename T>
class win_thread_base
{
public:
  static bool terminate_threads()
  {
    return ::InterlockedExchangeAdd(&terminate_threads_, 0) != 0;
  }

  static void set_terminate_threads(bool b)
  {
    ::InterlockedExchange(&terminate_threads_, b ? 1 : 0);
  }

private:
  static long terminate_threads_;
};

template <typename T>
long win_thread_base<T>::terminate_threads_ = 0;

class win_thread
  : private noncopyable,
    public win_thread_base<win_thread>
{
public:
  // Constructor.
  template <typename Function>
  win_thread(Function f, unsigned int stack_size = 0)
    : thread_(0),
      exit_event_(0)
  {
    start_thread(new func<Function>(f), stack_size);
  }

  // Destructor.
  HBOOST_ASIO_DECL ~win_thread();

  // Wait for the thread to exit.
  HBOOST_ASIO_DECL void join();

private:
  friend HBOOST_ASIO_DECL unsigned int __stdcall win_thread_function(void* arg);

#if defined(WINVER) && (WINVER < 0x0500)
  friend HBOOST_ASIO_DECL void __stdcall apc_function(ULONG);
#else
  friend HBOOST_ASIO_DECL void __stdcall apc_function(ULONG_PTR);
#endif

  class func_base
  {
  public:
    virtual ~func_base() {}
    virtual void run() = 0;
    ::HANDLE entry_event_;
    ::HANDLE exit_event_;
  };

  struct auto_func_base_ptr
  {
    func_base* ptr;
    ~auto_func_base_ptr() { delete ptr; }
  };

  template <typename Function>
  class func
    : public func_base
  {
  public:
    func(Function f)
      : f_(f)
    {
    }

    virtual void run()
    {
      f_();
    }

  private:
    Function f_;
  };

  HBOOST_ASIO_DECL void start_thread(func_base* arg, unsigned int stack_size);

  ::HANDLE thread_;
  ::HANDLE exit_event_;
};

} // namespace detail
} // namespace asio
} // namespace hboost

#include <hboost/asio/detail/pop_options.hpp>

#if defined(HBOOST_ASIO_HEADER_ONLY)
# include <hboost/asio/detail/impl/win_thread.ipp>
#endif // defined(HBOOST_ASIO_HEADER_ONLY)

#endif // defined(HBOOST_ASIO_WINDOWS)
       // && !defined(HBOOST_ASIO_WINDOWS_APP)
       // && !defined(UNDER_CE)

#endif // HBOOST_ASIO_DETAIL_WIN_THREAD_HPP
