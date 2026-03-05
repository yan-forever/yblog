cmake_minimum_required(VERSION 3.10)
project(yblog CXX)
# 强制C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 寻找drogon
find_package(Drogon CONFIG REQUIRED)
# 添加主程序源文件
add_executable(${PROJECT_NAME} main.cpp)
# 将drogon的动态库链接到我们的 yblog 程序上
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
