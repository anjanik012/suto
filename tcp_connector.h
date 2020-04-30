//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/30/20.
//

#ifndef SUTO_TCP_CONNECTOR_H
#define SUTO_TCP_CONNECTOR_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class tcp_connector {
private:
    io_service &m_service;

    static const uint16_t PORT = 2022;

    bool is_started = false;
    bool is_connected = false;

    tcp::socket m_socket;
    tcp::endpoint m_remote;

    bool connect_to_device();
    void connect_handler(const boost::system::error_code &);
public:
    explicit tcp_connector(io_service &serv): m_service(serv), m_socket(serv) {}
    void set_endpoint(udp::endpoint &endpoint);

    void start();
    void stop();
};


#endif //SUTO_TCP_CONNECTOR_H
