cmake_minimum_required(VERSION 3.12)

# Use hunter to download and build some third party dependencies
include("external/cmake/HunterGate.cmake")
huntergate(URL "https://github.com/cpp-pm/hunter/archive/v0.23.279.tar.gz" SHA1 "0a8ede485c3e9c1ceed8ccb989ab6c0aba1f4db7")


project(aeb)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(CMAKE_CXX_STANDARD 17)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(aeb
    STATIC
    eb/eventbus_impl.h
    eb/eventbus_impl.cpp
    eb/eventlistener.h
    eb/eventbus.h
    )


#example
add_executable(aeb_example
    example/example.cpp)
target_include_directories(aeb_example PRIVATE "eb")
target_link_libraries(aeb_example aeb)

# tests
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows") # disable for now, there is a linker problem...
    file(GLOB TEST_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")
    add_executable(aeb_test ${TEST_SRC_FILES})
    target_include_directories(aeb_test PRIVATE "eb")
    target_link_libraries(aeb_test GTest::gtest)
    target_link_libraries(aeb_test aeb)

    enable_testing()
    add_test(NAME aeb_test COMMAND aeb_test)
endif()
