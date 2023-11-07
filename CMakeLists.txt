cmake_minimum_required(VERSION 3.0.0)
project(delay VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(delay main.cpp)
add_subdirectory(csvlogger)


target_link_libraries(delay PRIVATE csvlogger)
target_compile_options(delay PRIVATE -Wall -pthread)
target_link_libraries(delay PRIVATE pigpio rt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
