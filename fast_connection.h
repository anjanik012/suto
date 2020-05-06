//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/2/20.
//

#ifndef SUTO_FAST_CONNECTION_H
#define SUTO_FAST_CONNECTION_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/network_v4.hpp>

#include "protocol.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class fast_connection {
private:
    io_service &service;
    static const int UDP_BROADCAST_PORT = 2020;
    static const int TCP_LISTEN_PORT = 2021;

    static const std::string UDP_HELLO;

    udp::socket broadcast_socket;
    udp::endpoint broadcast_addr;
    bool send_broadcast();
    void broadcast_handle(const boost::system::error_code &, std::size_t);

    tcp::socket m_socket;
    tcp::endpoint listener_endpoint;
    tcp::acceptor acceptor;
    bool listen_for_tcp();
    void tcp_connection_established(const boost::system::error_code &);

    protocol p;
public:
    explicit fast_connection(io_service &serv) :
            service(serv), broadcast_socket(serv),
            m_socket(serv),
            acceptor(serv, tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT)) {
        broadcast_addr = udp::endpoint(network_v4().broadcast(), UDP_BROADCAST_PORT);
        listener_endpoint = tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT);
    }

    void start();

    void stop();
};


#endif //SUTO_FAST_CONNECTION_H
