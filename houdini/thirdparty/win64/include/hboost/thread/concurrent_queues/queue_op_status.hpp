#ifndef HBOOST_THREAD_QUEUE_OP_STATUS_HPP
#define HBOOST_THREAD_QUEUE_OP_STATUS_HPP

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/thread for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <hboost/thread/detail/config.hpp>
#include <hboost/thread/detail/move.hpp>

#include <hboost/config/abi_prefix.hpp>

namespace hboost
{
namespace concurrent
{

  HBOOST_SCOPED_ENUM_DECLARE_BEGIN(queue_op_status)
  { success = 0, empty, full, closed, busy, timeout, not_ready }
  HBOOST_SCOPED_ENUM_DECLARE_END(queue_op_status)

  struct sync_queue_is_closed : std::exception
  {
  };

}

#ifndef HBOOST_THREAD_QUEUE_DEPRECATE_OLD
  struct no_block_tag{};
  HBOOST_CONSTEXPR_OR_CONST no_block_tag no_block = {};
#endif

  using concurrent::queue_op_status;
  using concurrent::sync_queue_is_closed;

}

#include <hboost/config/abi_suffix.hpp>

#endif
