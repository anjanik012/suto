cmake_minimum_required(VERSION 3.13)
project(suto C CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.42.0 REQUIRED COMPONENTS system thread random log)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD OFF)

set(CMAKE_CXX_FLAGS "-fPIC -fno-stack-protector -DBOOST_LOG_DYN_LINK")

if(logging)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dlogging")
endif()

add_subdirectory(src)

set(LIB_SYS ${Boost_SYSTEM_LIBRARY})
set(LIB_THREAD ${Boost_THREAD_LIBRARY})
set(LIB_RANDOM ${Boost_RANDOM_LIBRARY})
set(LIB_CRYPT crypt)
set(LIB_PTHREAD pthread)
set(LIB_LOG ${Boost_LOG_LIBRARY})

add_library(pam_suto SHARED
        $<TARGET_OBJECTS:suto_pam>
        $<TARGET_OBJECTS:authenticator>
        $<TARGET_OBJECTS:protocol>
        $<TARGET_OBJECTS:fast_connection>
        $<TARGET_OBJECTS:random_salt>
        $<TARGET_OBJECTS:logger>
        )
set_target_properties(pam_suto PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pam_suto ${LIB_SYS} ${LIB_THREAD} ${LIB_RANDOM} ${LIB_CRYPT} ${LIB_LOG} ${LIB_PTHREAD})
install(TARGETS pam_suto DESTINATION lib/security)
