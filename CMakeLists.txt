cmake_minimum_required(VERSION 3.10)

project(main LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")

add_executable(main main.cpp ${SOURCES})

target_include_directories(main PUBLIC ${main_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${main_SOURCE_DIR})