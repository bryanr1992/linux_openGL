cmake_minimum_required(VERSION 3.16)
project(cherno_gl_tut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(triangle_gl src/main.cpp)

target_link_libraries(triangle_gl
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)
