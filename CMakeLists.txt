cmake_minimum_required(VERSION 3.10)

project(aeb)

set(CMAKE_CXX_STANDARD 17)

add_library(aeb
    STATIC
    eb/eventbus_impl.h
    eb/eventbus_impl.cpp
    eb/eventlistener.h
    eb/eventbus.h
    )


add_executable(example
    example/example.cpp)

target_include_directories(example PRIVATE "eb")
target_link_libraries(example aeb)
