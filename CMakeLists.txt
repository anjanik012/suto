cmake_minimum_required(VERSION 3.16)
project(suto)

set(CMAKE_CXX_STANDARD 14)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread random)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_RANDOM_LIBRARY})

add_executable(suto main.cpp fast_connection.cpp fast_connection.h random_salt.cpp random_salt.h)
TARGET_LINK_LIBRARIES(suto ${USED_LIBS})