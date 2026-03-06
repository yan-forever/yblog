cmake_minimum_required(VERSION 3.10)
project(yblog CXX)
# 强制C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 寻找drogon
find_package(Drogon CONFIG REQUIRED)
# 添加源文件
set(SRC_FILES
        main.cpp
        models/Posts.cc
        models/PostTags.cc
        models/Tags.cc
        models/Users.cc
        controllers/api_v1_PostController.cc
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/models)
add_executable(${PROJECT_NAME} ${SRC_FILES})
# 将drogon的动态库链接到我们的 yblog 程序上
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
