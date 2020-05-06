//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

#ifndef SUTO_PROTOCOL_H
#define SUTO_PROTOCOL_H

#include <boost/lockfree/stack.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include "random_salt.h"
#include "authenticator.h"

using namespace boost::lockfree;
using namespace boost::asio::ip;
using std::string;

class protocol {
private:
    stack<string, capacity<10>> steps;
    const string GET_SALT = "SUTO_C_GET_SALT";
    const string GET_RSALT = "SUTO_C_GET_RSALT";
    const string GET_FHASH = "SUTO_C_F_HASH";

    const string AUTH_SUCCESS = "SUTO_AUTH_SUCCESS";
    const string AUTH_FAILED = "SUTO_AUTH_FAILED";

    string read_buffer;

    authenticator m_authenticator;

    tcp::socket *m_socket;

    bool start_read();

    bool start_write();

    void read_handler(const boost::system::error_code &, std::size_t);

    void write_handler(const boost::system::error_code &, std::size_t);

    bool validate_msg();

    void send_auth_msg(bool);

public:
    protocol();

    bool set_tcp_socket(tcp::socket *);

    void start_auth_job();
};


#endif //SUTO_PROTOCOL_H
