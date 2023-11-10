# distance_sensor/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(distance_sensor)

find_package(catkin REQUIRED COMPONENTS
    serial
)

include_directories(
    include
)

file(GLOB SOURCES "src/*.cpp")
add_library(distance_sensor SHARED ${SOURCES})
add_subdirectory(../serial)
target_compile_options(distance_sensor PRIVATE -Wall -pthread)
target_link_libraries(distance_sensor PRIVATE pigpio rt)
target_include_directories(distance_sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(distance_sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)