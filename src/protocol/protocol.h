/*
Copyright 2020 Anjani Kumar <anjanik012@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SUTO_PROTOCOL_H
#define SUTO_PROTOCOL_H

#include <boost/lockfree/stack.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include "random_salt.h"
#include "authenticator.h"
#include "auth_complete_callback.h"

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
    auth_complete_callback *m_callback;

    tcp::socket *m_socket;

    bool start_read();

    bool start_write();

    void read_handler(const boost::system::error_code &, std::size_t);

    void write_handler(const boost::system::error_code &, std::size_t);

    bool validate_msg();

    void send_auth_msg(bool);

    void *m_user_to_auth;

public:
    explicit protocol(void *);

    bool set_tcp_socket(tcp::socket *);
    void set_auth_completion_callback(auth_complete_callback *);

    void start_auth_job();
};


#endif //SUTO_PROTOCOL_H
