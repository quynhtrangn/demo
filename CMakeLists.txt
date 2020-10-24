
cmake_minimum_required(VERSION 3.17)
project(game1)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.5.1 COMPONENTS system window graphics)

add_executable(game1 main.cpp)
target_link_libraries(game1 sfml-system sfml-window sfml-graphics sfml-audio)