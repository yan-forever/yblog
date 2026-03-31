cmake_minimum_required(VERSION 3.10)
project(yblog CXX)

# 强制C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)


file(GLOB MODEL_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/models/*.cc")

set(SRC_FILES
        main.cc
        controllers/api_v1_Articles.cc
        ${MODEL_SRCS}
)

add_executable(${PROJECT_NAME} ${SRC_FILES})


target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        ${CMAKE_CURRENT_SOURCE_DIR}/controllers
        ${CMAKE_CURRENT_SOURCE_DIR}/dto
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Drogon::Drogon
        yaml-cpp::yaml-cpp
        OpenSSL::SSL
        OpenSSL::Crypto
        unofficial::brotli::brotlidec
        unofficial::brotli::brotlienc
        unofficial::brotli::brotlicommon
)