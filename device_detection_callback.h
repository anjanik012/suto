//
// Created by Anjani Kumar <anjani012@gmail.com> on 4/29/20.
//

#ifndef SUTO_DEVICE_DETECTION_CALLBACK_H
#define SUTO_DEVICE_DETECTION_CALLBACK_H

#include <boost/asio/ip/udp.hpp>

class device_detection_callback{
public:
    virtual void device_detected(boost::asio::ip::udp::endpoint &endpoint, std::size_t bytes_received) = 0;
};


#endif //SUTO_DEVICE_DETECTION_CALLBACK_H
