include_directories(${PROJECT_SOURCE_DIR}/src/random_salt)
include_directories(${PROJECT_SOURCE_DIR}/src/logger)

add_library(authenticator OBJECT authenticator.cpp)