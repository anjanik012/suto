cmake_minimum_required(VERSION 3.16)
project(suto)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread random)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD OFF)

add_subdirectory(src)
