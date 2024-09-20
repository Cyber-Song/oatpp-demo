cmake_minimum_required(VERSION 3.10)
project(my_oatpp_project)

set(CMAKE_CXX_STANDARD 17)

# 找到 Oat++ 包
find_package(oatpp REQUIRED)

# 编译项目
add_executable(my_oatpp_project src/main.cpp)

# 链接 Oat++ 库
target_link_libraries(my_oatpp_project oatpp::oatpp)

