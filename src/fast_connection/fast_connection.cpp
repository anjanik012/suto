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

#include "fast_connection.h"

#include <iostream>

const std::string fast_connection::UDP_HELLO = "SUTO_";

fast_connection::fast_connection(io_service &serv, void *user) :
        service(serv), broadcast_socket(serv),
        m_socket(serv),
        acceptor(serv, tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT)),
        m_tcp_clock(serv, boost::posix_time::seconds(4)),
        p(user){
    broadcast_addr = udp::endpoint(network_v4().broadcast(), UDP_BROADCAST_PORT);
    listener_endpoint = tcp::endpoint(tcp::v4(), TCP_LISTEN_PORT);
    user_to_auth = (struct spwd *)user;
    gethostname(m_hostname, HOSTNAME_MAX_LENGTH);
    hello_msg = UDP_HELLO + user_to_auth->sp_namp + '@' + m_hostname + '$';
}

void fast_connection::start() {
    broadcast_socket.open(udp::v4());
    broadcast_socket.set_option(udp::socket::reuse_address(true));
    broadcast_socket.set_option(socket_base::broadcast(true));
    send_broadcast();
    auto tcp_result = listen_for_tcp();
    if(tcp_result) {
        m_tcp_clock.async_wait(boost::bind(&fast_connection::tcp_timeout, this,
                                             boost::asio::placeholders::error));
    }
    service.run();
}

bool fast_connection::send_broadcast() {
    try {
        broadcast_socket.async_send_to(buffer(hello_msg, hello_msg.size()), broadcast_addr,
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
        m_broadcast_num++;
        std::cout << "UDP: Sent Broadcast with message:-" << hello_msg << '\n';
        deadline_timer timer(service, boost::posix_time::seconds(2));
        timer.wait();
        if(m_broadcast_num != BROADCAST_LIMIT) {
            send_broadcast();
        }
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

void fast_connection::tcp_timeout(const boost::system::error_code &ec) {
    if(!ec) {
        if(!m_socket.is_open()) {
            acceptor.close();
            std::cerr << "UDP: No reply received for broadcasts... Aborting :(\n";
        }
    }
}

void fast_connection::tcp_connection_established(const boost::system::error_code &ec) {
    if (!ec) {
        m_tcp_clock.cancel();
        stop_broadcast();
        std::cout << "TCP: Connection established with:-" << m_socket.remote_endpoint().address().to_string() << '\n';
        if (p.set_tcp_socket(&m_socket)) {
            std::cout << "TCP: Socket passed to protocol for further processing\n";
        } else {
            std::cerr << "TCP: oops!!! socket got closed somehow :(\n";
        }
        p.set_auth_completion_callback(this);
        p.start_auth_job();
    }
}

void fast_connection::stop_broadcast() {
    broadcast_socket.close();
//    m_socket.close();
}

void fast_connection::on_auth_complete() {
    is_auth_success = true;
}

bool fast_connection::get_auth_status() {
    return is_auth_success;
}

//void fast_connection::set_user_to_auth(void *user) {
//    user_to_auth = user;
//}




