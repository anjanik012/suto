//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/29/20.
//

#include "connection.h"
#include "tcp_connector.h"

void connection::start() {
    m_finder.set_callback(this);
    m_finder.start();
}

void connection::close() {
    m_finder.stop();
}

void connection::device_detected(ip::udp::endpoint &remote, std::size_t bytes_received) {
    std::cout << "Reply received from:-" << remote.address().to_string() << std::endl;
    std::cout << "Bytes received:-" << bytes_received << std::endl;

    tcp_connector connector(service);
    connector.set_endpoint(remote);
    connector.start();
}

