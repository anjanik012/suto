/*
Copyright 2020 Anjani Kumar <anjanik012@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SUTO_FAST_CONNECTION_H
#define SUTO_FAST_CONNECTION_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/deadline_timer.hpp>

#include<unistd.h>

#include "protocol.h"
#include "auth_complete_callback.h"

#define HOSTNAME_MAX_LENGTH 254
#define BROADCAST_LIMIT 2

using namespace boost::asio;
using namespace boost::asio::ip;

class fast_connection : public auth_complete_callback {
private:
    io_service &service;
    static const int UDP_BROADCAST_PORT = 2020;
    static const int TCP_LISTEN_PORT = 2021;

    static const std::string UDP_HELLO;
    std::string hello_msg;
    char m_hostname[HOSTNAME_MAX_LENGTH];
    int m_broadcast_num = 0;

    udp::socket broadcast_socket;
    udp::endpoint broadcast_addr;

    bool send_broadcast();

    void broadcast_handle(const boost::system::error_code &, std::size_t);

    tcp::socket m_socket;
    tcp::endpoint listener_endpoint;
    tcp::acceptor acceptor;
    deadline_timer m_tcp_clock;

    bool listen_for_tcp();
    void tcp_timeout(const boost::system::error_code &);

    void tcp_connection_established(const boost::system::error_code &);

    protocol p;

    bool is_auth_success = false;

    void on_auth_complete() override;

    struct spwd *user_to_auth = nullptr;
public:
    explicit fast_connection(io_service &, void *);

    void start();

    void stop_broadcast();

//    void set_user_to_auth(void *);
    bool get_auth_status();
};


#endif //SUTO_FAST_CONNECTION_H
