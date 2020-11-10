include_directories(${PROJECT_SOURCE_DIR}/src/auth_callback)
include_directories(${PROJECT_SOURCE_DIR}/src/random_salt)
include_directories(${PROJECT_SOURCE_DIR}/src/authenticator)
include_directories(${PROJECT_SOURCE_DIR}/src/logger)

add_library(protocol OBJECT protocol.cpp)