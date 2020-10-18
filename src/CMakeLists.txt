set(SYS_LIB ${Boost_SYSTEM_LIBRARY})
set(THREAD_LIB ${Boost_THREAD_LIBRARY})
set(RANDOM_LIB ${Boost_RANDOM_LIBRARY})
set(CRYPT_LIB crypt)

set(CMAKE_CXX_FLAGS "-fPIC -fno-stack-protector")

add_subdirectory(authenticator)
add_subdirectory(fast_connection)
add_subdirectory(protocol)
add_subdirectory(random_salt)

include_directories(fast_connection)
include_directories(protocol)
include_directories(authenticator)
include_directories(auth_callback)
include_directories(random_salt)

add_library(suto_pam SHARED suto_pam.cpp authenticator/authenticator.cpp fast_connection/fast_connection.cpp protocol/protocol.cpp random_salt/random_salt.cpp)

target_link_libraries(suto_pam ${SYS_LIBS} ${THREAD_LIB} ${RANDOM_LIB} ${CRYPT_LIB})
