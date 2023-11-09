cmake_minimum_required(VERSION 3.0.0)
project(calibrazione VERSION 0.1.0 LANGUAGES C CXX)

add_executable(calibra main.cpp)
add_subdirectory(csvlogger)
add_subdirectory(distance_sensor)


target_link_libraries(calibra PRIVATE csvlogger)
target_link_libraries(calibra PRIVATE distance_sensor)
target_compile_options(calibra PRIVATE -Wall -pthread)
target_link_libraries(calibra PRIVATE pigpio rt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
