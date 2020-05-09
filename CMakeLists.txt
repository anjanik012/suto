cmake_minimum_required(VERSION 3.16)
project(suto)

set(CMAKE_CXX_STANDARD 14)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread random)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_RANDOM_LIBRARY} crypt)
SET(CMAKE_CXX_FLAGS "-fPIC -fno-stack-protector")

add_library(suto_pam STATIC fast_connection.cpp fast_connection.h random_salt.cpp random_salt.h protocol.cpp protocol.h authenticator.cpp authenticator.h suto_pam.cpp auth_complete_callback.h)
TARGET_LINK_LIBRARIES(suto_pam ${USED_LIBS})