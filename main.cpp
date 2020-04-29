#include <iostream>
#include <boost/asio/io_service.hpp>

#include "device_discovery.h"

using std::cout;
using std::cin;
using std::endl;
using namespace boost::asio;

int main() {
    io_service service;
    device_discovery finder(service);
    finder.start();
    return 0;
}
