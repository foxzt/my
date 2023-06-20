cmake_minimum_required(VERSION 3.22)
project(my)

set(CMAKE_CXX_STANDARD 11)

set(LIB_SRC
        sylar/log.cc
        sylar/util.cc
        sylar/config.h)
add_library(mylib STATIC ${LIB_SRC})
set_target_properties(mylib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)


add_executable(my main.cpp)

add_executable(log_test tests/test.cc)
target_link_libraries(log_test mylib)
set_target_properties(log_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


add_executable(config_test tests/test_config.cc)
target_link_libraries(config_test mylib)
set_target_properties(config_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)