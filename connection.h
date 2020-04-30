//
// Created by Anjani Kumar <anjanik012@gmail.com> on 4/29/20.
//

#ifndef SUTO_CONNECTION_H
#define SUTO_CONNECTION_H


#include "device_detection_callback.h"
#include "tcp_connector_callback.h"

#include "device_discovery.h"
#include "tcp_connector.h"

class connection : public device_detection_callback, tcp_connector_callback{
private:
    io_service &service;
    device_discovery m_finder;
    tcp_connector m_connection;
public:
    explicit connection(io_service &serv): service(serv), m_finder(serv), m_connection(serv) {};
    void start();
    void close();

    void device_detected(ip::udp::endpoint &remote, std::size_t bytes_received) override;
    void tcp_connection_established() override;
};


#endif //SUTO_CONNECTION_H
