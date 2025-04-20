cmake_minimum_required(VERSION 3.10.0)
project(TinyRender VERSION 0.1.0 LANGUAGES C CXX)

find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(src)

add_executable(TinyRender main.cpp)

target_link_libraries(TinyRender PRIVATE glm::glm SDL2::SDL2 SDL2::SDL2main src)
