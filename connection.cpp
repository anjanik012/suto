//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/29/20.
//

#include "connection.h"
#include "tcp_connector.h"

void connection::start() {
    m_finder.set_callback(this);
    m_connection.set_connector_callback(this);
    m_finder.start();
}

void connection::close() {
    m_finder.stop();
}

void connection::device_detected(ip::udp::endpoint &remote, std::size_t bytes_received) {
    std::cout << "Reply received from:-" << remote.address().to_string() << std::endl;
    std::cout << "Bytes received:-" << bytes_received << std::endl;

    m_connection.set_endpoint(remote);
    m_connection.start();
}

void connection::tcp_connection_established() {
    std::cout << "TCP connection established with " << m_connection.get_remote_address() << std::endl;
    bool res = m_connection.write_data("Hello There!!!");
    if (res) {
        std::cout << "Data Written" << std::endl;
    } else {
        std::cerr << "Data writing failed" << std::endl;
    }
}

