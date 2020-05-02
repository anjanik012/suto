#include <boost/asio/io_service.hpp>

#include "fast_connection.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using namespace boost::asio;

int main() {
    io_service service;
    fast_connection connection(service);
    connection.start();
    return 0;
}
