cmake_minimum_required(VERSION 3.22)
project(my)

# 指定C++标准
set(CMAKE_CXX_STANDARD 11)

# 将所有文件编译成静态库
set(LIB_SRC
        sylar/log.cc
        sylar/util.cc
        sylar/config.cpp)
add_library(mylib STATIC ${LIB_SRC})

# 测试demo
add_executable(my main.cpp)

# 测试log
add_executable(log_test tests/test.cc)
add_dependencies(log_test mylib)
target_link_libraries(log_test PRIVATE mylib)

# 测试config
add_executable(config_test tests/test_config.cc)
add_dependencies(config_test mylib)
target_link_libraries(config_test PRIVATE mylib)

# 设置所有可执行文件的输出路径为项目根目录下的bin文件夹
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置所有库文件的输出路径为项目根目录下的lib文件夹
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)