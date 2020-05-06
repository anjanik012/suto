//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

#include "protocol.h"

#include <iostream>

using std::string;
using namespace boost::asio;

protocol::protocol() : steps(), salter() {
    steps.push(GET_FHASH);
    steps.push(GET_RSALT);
    steps.push(GET_SALT);
    m_socket = nullptr;
    read_buffer.resize(200);
}

bool protocol::validate_msg() {
    bool ans = false;
    string step;
    steps.pop(step);
    if (read_buffer.find(step) != string::npos) {
        ans = true;
    }
    return ans;
}

bool protocol::set_tcp_socket(tcp::socket *socket) {
    bool ans;
    if (socket->is_open()) {
        m_socket = socket;
        ans = true;
    } else {
        ans = false;
    }
    return ans;
}

void protocol::start_auth_job() {
    bool read_status = start_read();
    if (read_status) {
        std::cout << "PROTOCOL: Waiting for message" << std::endl;
    } else {
        std::cout << "PROTOCOL: Can't read :(" << std::endl;
    }

}

bool protocol::start_read() {
    try {
        m_socket->async_read_some(buffer(read_buffer, read_buffer.size()), boost::bind(
                &protocol::read_handler, this,
                placeholders::error,
                placeholders::bytes_transferred));
    } catch (boost::system::system_error &error) {
        return false;
    }
    return true;
}

bool protocol::start_write() {
    try {
        string reply;
        if (read_buffer.find(GET_SALT) != string::npos) {
            reply = "SUTO_SALT_";
            reply += salter.get_salt(15);
        } else if (read_buffer.find(GET_RSALT) != string::npos) {
            reply = "SUTO_RSALT_";
            reply += salter.get_salt(15);
        }
        m_socket->async_write_some(buffer(reply), boost::bind(
                &protocol::write_handler, this,
                placeholders::error,
                placeholders::bytes_transferred));
    } catch (boost::system::system_error &error) {
        return false;
    }
    return true;
}

void protocol::read_handler(const boost::system::error_code &ec, std::size_t bytes) {
    if (!ec) {
        std::cout << "PROTOCOL: message received:-" << read_buffer << std::endl;
        if (!steps.empty()) {
            if (validate_msg() && (read_buffer.find(GET_FHASH) == string::npos)) {
                std::cout << "PROTOCOL: Message validated...sending reply" << std::endl;
                start_write();
            } else if (read_buffer.find(GET_FHASH) != string::npos){
                std::cout << "PROTOCOL: Final hash received" << std::endl;
            } else {
                std::cerr << "PROTOCOL: Unknown message received...stopping :|" << std::endl;
            }
        }
    } else {
        std::cerr << "PROTOCOL: read failed :|" << std::endl;
    }
}

void protocol::write_handler(const boost::system::error_code &ec, std::size_t bytes) {
    if (!ec) {
        std::cout << "PROTOCOL: Messgage sent :)...Waiting for next message" <<std::endl;
        start_read();
    } else {
        std::cerr << "PROTOCOL: Failed sending message :(" << std::endl;
    }
}
