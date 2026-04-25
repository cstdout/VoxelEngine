cmake_minimum_required(VERSION 3.16)

project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)


set(GLFW_BUILD_DOCS OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew-2.3.1/build/cmake)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} "main.cpp")

target_link_libraries(${PROJECT_NAME} glfw glew)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.3.1/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4/include)
