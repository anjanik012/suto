//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/30/20.
//

#ifndef SUTO_TCP_CONNECTOR_H
#define SUTO_TCP_CONNECTOR_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/placeholders.hpp>

#include "tcp_connector_callback.h"

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

    tcp_connector_callback *m_callback = nullptr;
public:
    explicit tcp_connector(io_service &serv): m_service(serv), m_socket(serv) {}
    void set_endpoint(udp::endpoint &endpoint);
    void set_connector_callback(tcp_connector_callback *);

    void start();
    void stop();

    std::string get_remote_address();
    bool write_data(const std::string &);
};


#endif //SUTO_TCP_CONNECTOR_H
