//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/27/20.
//

#ifndef SUTO_DEVICE_DISCOVERY_H
#define SUTO_DEVICE_DISCOVERY_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <iostream>
#include <array>

using namespace boost::asio;
using std::string;
using std::array;

class device_discovery {
private:
    io_service &service;
    static const uint16_t SEND_PORT = 2020;
    static const uint16_t RECEIVE_PORT = 2021;
    ip::udp::socket send_socket, receive_socket;
    ip::udp::endpoint broadcast_addr, receive_addr;
    static const string UDP_HELLO;
    static const string UDP_HELLO_REPLY;
    array<char, 20> receive_buffer;
    bool send_broadcast(ip::udp::endpoint &);
    bool receive_broadcast_reply(ip::udp::endpoint &);
    void handle_send(const boost::system::error_code &, std::size_t);
    void handle_receive(const boost::system::error_code &, std::size_t);
public:
    explicit device_discovery(io_service &serv):service(serv), send_socket(serv), receive_socket(serv) {
        broadcast_addr = ip::udp::endpoint(ip::network_v4().broadcast(), SEND_PORT);
        receive_addr = ip::udp::endpoint(ip::address_v4::any(), RECEIVE_PORT);
    }

    void start();
    void stop();
    ~device_discovery() {
        send_socket.close();
        receive_socket.close();
    }
};


#endif //SUTO_DEVICE_DISCOVERY_H
