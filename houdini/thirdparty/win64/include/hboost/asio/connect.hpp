//
// connect.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HBOOST_ASIO_CONNECT_HPP
#define HBOOST_ASIO_CONNECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <hboost/asio/detail/config.hpp>
#include <hboost/asio/async_result.hpp>
#include <hboost/asio/basic_socket.hpp>
#include <hboost/asio/error.hpp>

#include <hboost/asio/detail/push_options.hpp>

namespace hboost {
namespace asio {

/**
 * @defgroup connect hboost::asio::connect
 *
 * @brief Establishes a socket connection by trying each endpoint in a sequence.
 */
/*@{*/

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws hboost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is hboost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * hboost::asio::connect(s, r.resolve(q)); @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to hboost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * hboost::system::error_code ec;
 * hboost::asio::connect(s, r.resolve(q), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, hboost::system::error_code& ec);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws hboost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is hboost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * hboost::asio::connect(s, i, end); @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to hboost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * hboost::system::error_code ec;
 * hboost::asio::connect(s, i, end, ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, hboost::system::error_code& ec);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws hboost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is hboost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * tcp::resolver::iterator i = hboost::asio::connect(
 *     s, r.resolve(q), my_connect_condition());
 * std::cout << "Connected to: " << i->endpoint() << std::endl; @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, ConnectCondition connect_condition);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to hboost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 * hboost::system::error_code ec;
 * tcp::resolver::iterator i = hboost::asio::connect(
 *     s, r.resolve(q), my_connect_condition(), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   std::cout << "Connected to: " << i->endpoint() << std::endl;
 * } @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    ConnectCondition connect_condition, hboost::system::error_code& ec);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws hboost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is hboost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * i = hboost::asio::connect(s, i, end, my_connect_condition());
 * std::cout << "Connected to: " << i->endpoint() << std::endl; @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to hboost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::iterator i = r.resolve(q), end;
 * tcp::socket s(io_service);
 * hboost::system::error_code ec;
 * i = hboost::asio::connect(s, i, end, my_connect_condition(), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   std::cout << "Connected to: " << i->endpoint() << std::endl;
 * } @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, ConnectCondition connect_condition,
    hboost::system::error_code& ec);

/*@}*/

/**
 * @defgroup async_connect hboost::asio::async_connect
 *
 * @brief Asynchronously establishes a socket connection by trying each
 * endpoint in a sequence.
 */
/*@{*/

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // hboost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const hboost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation
 * of the handler will be performed in a manner equivalent to using
 * hboost::asio::io_service::post().
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (!ec)
 *   {
 *     hboost::asio::async_connect(s, i, connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   // ...
 * } @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ComposedConnectHandler>
HBOOST_ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (hboost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, HBOOST_ASIO_MOVE_ARG(ComposedConnectHandler) handler);

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // hboost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const hboost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation
 * of the handler will be performed in a manner equivalent to using
 * hboost::asio::io_service::post().
 *
 * @par Example
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (!ec)
 *   {
 *     tcp::resolver::iterator end;
 *     hboost::asio::async_connect(s, i, end, connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   // ...
 * } @endcode
 */
template <typename Protocol, typename SocketService,
    typename Iterator, typename ComposedConnectHandler>
HBOOST_ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (hboost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end,
    HBOOST_ASIO_MOVE_ARG(ComposedConnectHandler) handler);

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // hboost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const hboost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation
 * of the handler will be performed in a manner equivalent to using
 * hboost::asio::io_service::post().
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c hboost::asio::ip::tcp::resolver::iterator.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (!ec)
 *   {
 *     hboost::asio::async_connect(s, i,
 *         my_connect_condition(),
 *         connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (ec)
 *   {
 *     // An error occurred.
 *   }
 *   else
 *   {
 *     std::cout << "Connected to: " << i->endpoint() << std::endl;
 *   }
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator,
    typename ConnectCondition, typename ComposedConnectHandler>
HBOOST_ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (hboost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s, Iterator begin,
    ConnectCondition connect_condition,
    HBOOST_ASIO_MOVE_ARG(ComposedConnectHandler) handler);

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code Iterator connect_condition(
 *     const hboost::system::error_code& ec,
 *     Iterator next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is an iterator pointing to the next
 * endpoint to be tried. The function object should return the next iterator,
 * but is permitted to return a different iterator so that endpoints may be
 * skipped. The implementation guarantees that the function object will never
 * be called with the end iterator.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // hboost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const hboost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. Invocation
 * of the handler will be performed in a manner equivalent to using
 * hboost::asio::io_service::post().
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   template <typename Iterator>
 *   Iterator operator()(
 *       const hboost::system::error_code& ec,
 *       Iterator next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next->endpoint() << std::endl;
 *     return next;
 *   }
 * }; @endcode
 * It would be used with the hboost::asio::connect function as follows:
 * @code tcp::resolver r(io_service);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(io_service);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (!ec)
 *   {
 *     tcp::resolver::iterator end;
 *     hboost::asio::async_connect(s, i, end,
 *         my_connect_condition(),
 *         connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const hboost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (ec)
 *   {
 *     // An error occurred.
 *   }
 *   else
 *   {
 *     std::cout << "Connected to: " << i->endpoint() << std::endl;
 *   }
 * } @endcode
 */
template <typename Protocol, typename SocketService, typename Iterator,
    typename ConnectCondition, typename ComposedConnectHandler>
HBOOST_ASIO_INITFN_RESULT_TYPE(ComposedConnectHandler,
    void (hboost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, SocketService>& s,
    Iterator begin, Iterator end, ConnectCondition connect_condition,
    HBOOST_ASIO_MOVE_ARG(ComposedConnectHandler) handler);

/*@}*/

} // namespace asio
} // namespace hboost

#include <hboost/asio/detail/pop_options.hpp>

#include <hboost/asio/impl/connect.hpp>

#endif
