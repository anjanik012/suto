//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/2/20.
//

#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "fast_connection.h"

#include <iostream>

const std::string fast_connection::UDP_HELLO = "SUTO_UDP_HELLO";

void fast_connection::start() {
    broadcast_socket.open(udp::v4());
    broadcast_socket.set_option(udp::socket::reuse_address(true));
    broadcast_socket.set_option(socket_base::broadcast(true));
    send_broadcast();
    listen_for_tcp();
    service.run();
}

bool fast_connection::send_broadcast() {
    try{
        broadcast_socket.async_send_to(buffer(UDP_HELLO, UDP_HELLO.size()), broadcast_addr,
                boost::bind(&fast_connection::broadcast_handle, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    } catch (boost::system::system_error &ec) {
        broadcast_socket.close();
        return false;
    }
    return true;
}

void fast_connection::broadcast_handle(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if (!ec) {
        std::cout << "Sent Broadcast with message:-" << UDP_HELLO << std::endl;
        deadline_timer timer(service, boost::posix_time::seconds(3));
        timer.wait();
        send_broadcast();
    }
}

void fast_connection::stop() {
    broadcast_socket.close();
//    m_socket.close();
}

bool fast_connection::listen_for_tcp() {
    try {
        acceptor.listen();
        acceptor.async_accept(m_socket, boost::bind(&fast_connection::tcp_connection_handler, this,
                boost::asio::placeholders::error));
    } catch (boost::system::system_error &ec) {
        return false;
    }
    return true;
}

void fast_connection::tcp_connection_handler(const boost::system::error_code &ec) {
    if (!ec) {
        stop();
        std::cout << "TCP connection established with:-" << m_socket.remote_endpoint().address().to_string() << std::endl;
        boost::system::error_code e;
        m_socket.write_some(buffer("Hello there!!!"), e);
        if (!e) {
           std::cout << "TCP: Data written:- Hello there!!!" << std::endl;
        }
    }
}



