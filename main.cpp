#include <iostream>
#include <boost/asio/io_service.hpp>

#include "connection.h"

using std::cout;
using std::cin;
using std::endl;
using namespace boost::asio;

int main() {
    io_service service;
    connection m_connection(service);
    m_connection.start();
    return 0;
}
