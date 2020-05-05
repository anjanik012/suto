#include <boost/asio/io_service.hpp>

#include "fast_connection.h"

#include <iostream>
//#include "random_salt.h"

using std::cout;
using std::cin;
using std::endl;
using namespace boost::asio;

int main() {
    io_service service;
    fast_connection connection(service);
    connection.start();
//    random_salt salter;
//    cout << salter.get_salt(10) << endl;
    return 0;
}
