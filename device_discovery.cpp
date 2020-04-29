//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/27/20.
//

#include "device_discovery.h"
#include <boost/asio/deadline_timer.hpp>

const string device_discovery::UDP_HELLO = "SUTO_UDP_HELLO";
const string device_discovery::UDP_HELLO_REPLY = "SUTO_UDP_HELLO_REPLY";

bool device_discovery::send_broadcast(ip::udp::endpoint &endpoint) {
    try {
        send_socket.async_send_to(buffer(UDP_HELLO, UDP_HELLO.size()), endpoint,
                                  boost::bind(&device_discovery::handle_send, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
    } catch (boost::system::system_error &exception) {
        send_socket.close();
        return false;
    }
    return true;
}

bool device_discovery::receive_broadcast_reply(ip::udp::endpoint &host) {
    try {
        receive_socket.async_receive_from(buffer(receive_buffer, 1024), host,
                                          boost::bind(&device_discovery::handle_receive, this,
                                                      boost::asio::placeholders::error,
                                                      boost::asio::placeholders::bytes_transferred));
    } catch (boost::system::error_code &ec) {
        receive_socket.close();
        return false;
    }
    return true;
}

void device_discovery::start() {
    send_socket.open(ip::udp::v4());
    send_socket.set_option(ip::udp::socket::reuse_address(true));
    send_socket.set_option(socket_base::broadcast(true));
    receive_socket.open(ip::udp::v4());
    receive_socket.set_option(socket_base::broadcast(true));
    receive_socket.bind(receive_addr);
    send_broadcast(broadcast_addr);
    receive_broadcast_reply(receive_addr);
    service.run();
}

void device_discovery::handle_send(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if (!ec && bytes_transferred > 0) {
        std::cout << "Bytes broadcasted:-" << bytes_transferred << std::endl;
        std::cout << "Data sent:-" << UDP_HELLO << std::endl;
        boost::asio::deadline_timer timer(service, boost::posix_time::seconds(3));
        timer.wait();
        send_broadcast(broadcast_addr);
    }
}

void device_discovery::handle_receive(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if (!ec) {
        string reply(receive_buffer.begin(), receive_buffer.end());
        string ip_remote = receive_addr.address().to_string();
        std::cout << "Received bytes:-" << bytes_transferred << " from:-" << ip_remote << std::endl;
        if (reply == UDP_HELLO_REPLY) {
            std::cout << reply << std::endl;
            stop();
        }
    }
}

void device_discovery::stop() {
    send_socket.close();
    receive_socket.close();
    service.stop();
}

