cmake_minimum_required(VERSION 3.16)
project(suto)

set(CMAKE_CXX_STANDARD 14)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(suto main.cpp device_discovery.cpp device_discovery.h device_detection_callback.h connection.cpp connection.h tcp_connector.cpp tcp_connector.h)
TARGET_LINK_LIBRARIES(suto ${USED_LIBS})