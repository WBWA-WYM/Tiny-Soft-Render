# src/CMakeLists.txt
file(GLOB_RECURSE SRC_SOURCES *.cpp)

add_library(src ${SRC_SOURCES})

target_link_libraries(src
  PUBLIC
    glm::glm
    SDL2::SDL2
    SDL2::SDL2main
)

target_include_directories(src
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}    # 项目自身头文件
)
