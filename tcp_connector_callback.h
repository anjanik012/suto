//
// Created by Anjani Kumar <anjaink012@gmail.com> on 4/30/20.
//

#ifndef SUTO_TCP_CONNECTOR_CALLBACK_H
#define SUTO_TCP_CONNECTOR_CALLBACK_H

#include <boost/asio/ip/tcp.hpp>

class tcp_connector_callback {
public:
    virtual void tcp_connection_established() = 0;
};

#endif //SUTO_TCP_CONNECTOR_CALLBACK_H
