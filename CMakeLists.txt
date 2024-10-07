cmake_minimum_required(VERSION 3.10)
project(cv2)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main ${SOURCES})

target_link_libraries(main OpenGL::GL glfw GLEW::GLEW)
