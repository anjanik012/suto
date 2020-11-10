#add_library(random_salt random_salt.cpp)
#target_link_libraries(random_salt ${THREAD_LIB})

add_library(random_salt OBJECT random_salt.cpp)