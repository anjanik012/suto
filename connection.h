//
// Created by anjani on 4/29/20.
//

#ifndef SUTO_CONNECTION_H
#define SUTO_CONNECTION_H


#include "device_detection_callback.h"
#include "device_discovery.h"

class connection : public device_detection_callback {
private:
    device_discovery m_finder;
    io_service &service;
public:
    explicit connection(io_service &serv): service(serv), m_finder(serv) {};
    void start();
    void close();

    void device_detected(ip::udp::endpoint &remote, std::size_t bytes_received) override;
};


#endif //SUTO_CONNECTION_H
