//
// detail/completion_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HBOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP
#define HBOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <hboost/asio/detail/addressof.hpp>
#include <hboost/asio/detail/config.hpp>
#include <hboost/asio/detail/fenced_block.hpp>
#include <hboost/asio/detail/handler_alloc_helpers.hpp>
#include <hboost/asio/detail/handler_invoke_helpers.hpp>
#include <hboost/asio/detail/operation.hpp>

#include <hboost/asio/detail/push_options.hpp>

namespace hboost {
namespace asio {
namespace detail {

template <typename Handler>
class completion_handler : public operation
{
public:
  HBOOST_ASIO_DEFINE_HANDLER_PTR(completion_handler);

  completion_handler(Handler& h)
    : operation(&completion_handler::do_complete),
      handler_(HBOOST_ASIO_MOVE_CAST(Handler)(h))
  {
  }

  static void do_complete(io_service_impl* owner, operation* base,
      const hboost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    completion_handler* h(static_cast<completion_handler*>(base));
    ptr p = { hboost::asio::detail::addressof(h->handler_), h, h };

    HBOOST_ASIO_HANDLER_COMPLETION((h));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    Handler handler(HBOOST_ASIO_MOVE_CAST(Handler)(h->handler_));
    p.h = hboost::asio::detail::addressof(handler);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      HBOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      hboost_asio_handler_invoke_helpers::invoke(handler, handler);
      HBOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace hboost

#include <hboost/asio/detail/pop_options.hpp>

#endif // HBOOST_ASIO_DETAIL_COMPLETION_HANDLER_HPP
