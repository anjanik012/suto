//
// Created by anjani on 4/30/20.
//

#include "tcp_connector.h"
#include <boost/bind.hpp>
#include <iostream>

void tcp_connector::set_endpoint(udp::endpoint &endpoint) {
    m_remote = tcp::endpoint(endpoint.address(), PORT);
}

void tcp_connector::start() {
    std::cout << "Starting a tcp connection with the reply device" << std::endl;
    is_started = true;
    m_socket.open(tcp::v4());
    bool res = connect_to_device();
    m_service.run();
    if (res) {
        std::cout << "TCP connection request made" << std::endl;
    } else {
        std::cout << "Failed to make TCP connection request" << std::endl;
    }
}

bool tcp_connector::connect_to_device() {
    try {
        m_socket.async_connect(m_remote, boost::bind(&tcp_connector::connect_handler, this,
                                                     boost::asio::placeholders::error));
    } catch (boost::system::system_error &ec) {
        m_socket.close();
        return false;
    }
    return true;
}

void tcp_connector::connect_handler(const boost::system::error_code &error) {
    if (!error) {
        is_connected = true;
        m_callback->tcp_connection_established();
    } else {
        std::cout << "TCP connection failed" << std::endl;
    }
}

void tcp_connector::stop() {
    m_socket.close();
    m_service.stop();
    is_started = is_connected = false;
}

void tcp_connector::set_connector_callback(tcp_connector_callback *callback) {
    m_callback = callback;
}

std::string tcp_connector::get_remote_address() {
    return m_remote.address().to_string();
}

bool tcp_connector::write_data(const std::string &data) {
    boost::system::error_code ec;
    auto bytes = m_socket.write_some(buffer(data), ec);
    return (!ec)? true : false;
}


