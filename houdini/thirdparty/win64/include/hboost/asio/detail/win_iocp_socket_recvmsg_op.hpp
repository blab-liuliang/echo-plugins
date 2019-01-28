//
// detail/win_iocp_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
#define HBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <hboost/asio/detail/config.hpp>

#if defined(HBOOST_ASIO_HAS_IOCP)

#include <hboost/asio/detail/addressof.hpp>
#include <hboost/asio/detail/bind_handler.hpp>
#include <hboost/asio/detail/buffer_sequence_adapter.hpp>
#include <hboost/asio/detail/fenced_block.hpp>
#include <hboost/asio/detail/handler_alloc_helpers.hpp>
#include <hboost/asio/detail/handler_invoke_helpers.hpp>
#include <hboost/asio/detail/operation.hpp>
#include <hboost/asio/detail/socket_ops.hpp>
#include <hboost/asio/error.hpp>
#include <hboost/asio/socket_base.hpp>

#include <hboost/asio/detail/push_options.hpp>

namespace hboost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler>
class win_iocp_socket_recvmsg_op : public operation
{
public:
  HBOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvmsg_op);

  win_iocp_socket_recvmsg_op(
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags, Handler& handler)
    : operation(&win_iocp_socket_recvmsg_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      out_flags_(out_flags),
      handler_(HBOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  static void do_complete(io_service_impl* owner, operation* base,
      const hboost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    hboost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recvmsg_op* o(
        static_cast<win_iocp_socket_recvmsg_op*>(base));
    ptr p = { hboost::asio::detail::addressof(o->handler_), o, o };

    HBOOST_ASIO_HANDLER_COMPLETION((o));

#if defined(HBOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<hboost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(HBOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recvmsg(o->cancel_token_, ec);
    o->out_flags_ = 0;

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, hboost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = hboost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      HBOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      hboost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      HBOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  socket_base::message_flags& out_flags_;
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace hboost

#include <hboost/asio/detail/pop_options.hpp>

#endif // defined(HBOOST_ASIO_HAS_IOCP)

#endif // HBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
