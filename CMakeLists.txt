cmake_minimum_required(VERSION 3.5.0)
project(sssl-discord-bot VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sssl-discord-bot main.cpp)

set(CMAKE_CXX_STANDARD 20)

find_package(dpp REQUIRED)

target_link_libraries(sssl-discord-bot PRIVATE dpp::dpp)
