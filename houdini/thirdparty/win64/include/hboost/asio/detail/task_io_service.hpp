//
// detail/task_io_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HBOOST_ASIO_DETAIL_TASK_IO_SERVICE_HPP
#define HBOOST_ASIO_DETAIL_TASK_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <hboost/asio/detail/config.hpp>

#if !defined(HBOOST_ASIO_HAS_IOCP)

#include <hboost/system/error_code.hpp>
#include <hboost/asio/io_service.hpp>
#include <hboost/asio/detail/atomic_count.hpp>
#include <hboost/asio/detail/call_stack.hpp>
#include <hboost/asio/detail/event.hpp>
#include <hboost/asio/detail/mutex.hpp>
#include <hboost/asio/detail/op_queue.hpp>
#include <hboost/asio/detail/reactor_fwd.hpp>
#include <hboost/asio/detail/task_io_service_operation.hpp>

#include <hboost/asio/detail/push_options.hpp>

namespace hboost {
namespace asio {
namespace detail {

struct task_io_service_thread_info;

class task_io_service
  : public hboost::asio::detail::service_base<task_io_service>
{
public:
  typedef task_io_service_operation operation;

  // Constructor. Specifies the number of concurrent threads that are likely to
  // run the io_service. If set to 1 certain optimisation are performed.
  HBOOST_ASIO_DECL task_io_service(hboost::asio::io_service& io_service,
      std::size_t concurrency_hint = 0);

  // Destroy all user-defined handler objects owned by the service.
  HBOOST_ASIO_DECL void shutdown_service();

  // Initialise the task, if required.
  HBOOST_ASIO_DECL void init_task();

  // Run the event loop until interrupted or no more work.
  HBOOST_ASIO_DECL std::size_t run(hboost::system::error_code& ec);

  // Run until interrupted or one operation is performed.
  HBOOST_ASIO_DECL std::size_t run_one(hboost::system::error_code& ec);

  // Poll for operations without blocking.
  HBOOST_ASIO_DECL std::size_t poll(hboost::system::error_code& ec);

  // Poll for one operation without blocking.
  HBOOST_ASIO_DECL std::size_t poll_one(hboost::system::error_code& ec);

  // Interrupt the event processing loop.
  HBOOST_ASIO_DECL void stop();

  // Determine whether the io_service is stopped.
  HBOOST_ASIO_DECL bool stopped() const;

  // Reset in preparation for a subsequent run invocation.
  HBOOST_ASIO_DECL void reset();

  // Notify that some work has started.
  void work_started()
  {
    ++outstanding_work_;
  }

  // Notify that some work has finished.
  void work_finished()
  {
    if (--outstanding_work_ == 0)
      stop();
  }

  // Return whether a handler can be dispatched immediately.
  bool can_dispatch()
  {
    return thread_call_stack::contains(this) != 0;
  }

  // Request invocation of the given handler.
  template <typename Handler>
  void dispatch(Handler& handler);

  // Request invocation of the given handler and return immediately.
  template <typename Handler>
  void post(Handler& handler);

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() has not yet been called for the operation.
  HBOOST_ASIO_DECL void post_immediate_completion(
      operation* op, bool is_continuation);

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operation.
  HBOOST_ASIO_DECL void post_deferred_completion(operation* op);

  // Request invocation of the given operations and return immediately. Assumes
  // that work_started() was previously called for each operation.
  HBOOST_ASIO_DECL void post_deferred_completions(op_queue<operation>& ops);

  // Process unfinished operations as part of a shutdown_service operation.
  // Assumes that work_started() was previously called for the operations.
  HBOOST_ASIO_DECL void abandon_operations(op_queue<operation>& ops);

private:
  // Structure containing thread-specific data.
  typedef task_io_service_thread_info thread_info;

  // Enqueue the given operation following a failed attempt to dispatch the
  // operation for immediate invocation.
  HBOOST_ASIO_DECL void do_dispatch(operation* op);

  // Run at most one operation. May block.
  HBOOST_ASIO_DECL std::size_t do_run_one(mutex::scoped_lock& lock,
      thread_info& this_thread, const hboost::system::error_code& ec);

  // Poll for at most one operation.
  HBOOST_ASIO_DECL std::size_t do_poll_one(mutex::scoped_lock& lock,
      thread_info& this_thread, const hboost::system::error_code& ec);

  // Stop the task and all idle threads.
  HBOOST_ASIO_DECL void stop_all_threads(mutex::scoped_lock& lock);

  // Wake a single idle thread, or the task, and always unlock the mutex.
  HBOOST_ASIO_DECL void wake_one_thread_and_unlock(
      mutex::scoped_lock& lock);

  // Helper class to perform task-related operations on block exit.
  struct task_cleanup;
  friend struct task_cleanup;

  // Helper class to call work-related operations on block exit.
  struct work_cleanup;
  friend struct work_cleanup;

  // Whether to optimise for single-threaded use cases.
  const bool one_thread_;

  // Mutex to protect access to internal data.
  mutable mutex mutex_;

  // Event to wake up blocked threads.
  event wakeup_event_;

  // The task to be run by this service.
  reactor* task_;

  // Operation object to represent the position of the task in the queue.
  struct task_operation : operation
  {
    task_operation() : operation(0) {}
  } task_operation_;

  // Whether the task has been interrupted.
  bool task_interrupted_;

  // The count of unfinished work.
  atomic_count outstanding_work_;

  // The queue of handlers that are ready to be delivered.
  op_queue<operation> op_queue_;

  // Flag to indicate that the dispatcher has been stopped.
  bool stopped_;

  // Flag to indicate that the dispatcher has been shut down.
  bool shutdown_;

  // Per-thread call stack to track the state of each thread in the io_service.
  typedef call_stack<task_io_service, thread_info> thread_call_stack;
};

} // namespace detail
} // namespace asio
} // namespace hboost

#include <hboost/asio/detail/pop_options.hpp>

#include <hboost/asio/detail/impl/task_io_service.hpp>
#if defined(HBOOST_ASIO_HEADER_ONLY)
# include <hboost/asio/detail/impl/task_io_service.ipp>
#endif // defined(HBOOST_ASIO_HEADER_ONLY)

#endif // !defined(HBOOST_ASIO_HAS_IOCP)

#endif // HBOOST_ASIO_DETAIL_TASK_IO_SERVICE_HPP
