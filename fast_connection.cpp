//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/2/20.
//

#include "fast_connection.h"

#include <iostream>

const std::string fast_connection::UDP_HELLO = "SUTO_UDP_HELLO";

fast_connection::fast_connection(io_service &serv) :
        service(serv), broadcast_socket(serv),
        m_socket(serv),
        acceptor(serv, tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT)) {
    broadcast_addr = udp::endpoint(network_v4().broadcast(), UDP_BROADCAST_PORT);
    listener_endpoint = tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT);
}

void fast_connection::start() {
    broadcast_socket.open(udp::v4());
    broadcast_socket.set_option(udp::socket::reuse_address(true));
    broadcast_socket.set_option(socket_base::broadcast(true));
    send_broadcast();
    listen_for_tcp();
    service.run();
}

bool fast_connection::send_broadcast() {
    try {
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
        std::cout << "UDP: Sent Broadcast with message:-" << UDP_HELLO << std::endl;
        deadline_timer timer(service, boost::posix_time::seconds(3));
        timer.wait();
        send_broadcast();
    }
}

bool fast_connection::listen_for_tcp() {
    try {
        acceptor.listen();
        acceptor.async_accept(m_socket, boost::bind(&fast_connection::tcp_connection_established, this,
                                                    boost::asio::placeholders::error));
    } catch (boost::system::system_error &ec) {
        return false;
    }
    return true;
}

void fast_connection::tcp_connection_established(const boost::system::error_code &ec) {
    if (!ec) {
        stop();
        std::cout << "TCP: Connection established with:-" << m_socket.remote_endpoint().address().to_string()
                  << std::endl;
        if (p.set_tcp_socket(&m_socket)) {
            std::cout << "TCP: Socket passed to protocol for further processing" << std::endl;
        } else {
            std::cerr << "TCP: oops!!! socket got closed somehow :(" << std::endl;
        }
        p.start_auth_job();
        service.run();
    }
}

void fast_connection::stop() {
    broadcast_socket.close();
//    m_socket.close();
}



