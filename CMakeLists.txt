cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 20)
project(calibrazione VERSION 0.1.0 LANGUAGES C CXX)

add_executable(calibrazione calibrazione.cpp)
add_executable(controltest controltest.cpp)
add_executable(rispostavelocita rispostavelocita.cpp)
add_executable(ritardosensore ritardosensore.cpp)
add_executable(ritardosensoreistruzione ritardosensoreistruzione.cpp)

add_subdirectory(csvlogger)
add_subdirectory(distance_sensor)
add_subdirectory(meca500_ethercat_cpp)

target_link_libraries(calibrazione PRIVATE csvlogger)
target_link_libraries(calibrazione PRIVATE distance_sensor)
target_compile_options(calibrazione PRIVATE -Wall -pthread)
target_link_libraries(calibrazione PRIVATE pigpio rt)
target_link_libraries(calibrazione PRIVATE meca500_driver)

target_link_libraries(controltest PRIVATE distance_sensor)
target_compile_options(controltest PRIVATE -Wall -pthread)
target_link_libraries(controltest PRIVATE pigpio rt)
target_link_libraries(controltest PRIVATE meca500_driver)

target_link_libraries(rispostavelocita PRIVATE csvlogger)
target_compile_options(rispostavelocita PRIVATE -Wall -pthread)
target_link_libraries(rispostavelocita PRIVATE pigpio rt)
target_link_libraries(rispostavelocita PRIVATE meca500_driver)

target_link_libraries(ritardosensore PRIVATE distance_sensor)
target_link_libraries(ritardosensore PRIVATE csvlogger)
target_compile_options(ritardosensore PRIVATE -Wall -pthread)
target_link_libraries(ritardosensore PRIVATE pigpio rt)
target_link_libraries(ritardosensore PRIVATE meca500_driver)

target_link_libraries(ritardosensoreistruzione PRIVATE distance_sensor)
target_link_libraries(ritardosensoreistruzione PRIVATE csvlogger)


target_compile_features(calibrazione PRIVATE cxx_std_17)
target_compile_features(controltest PRIVATE cxx_std_17)
target_compile_features(rispostavelocita PRIVATE cxx_std_17)
target_compile_features(ritardosensore PRIVATE cxx_std_17)
target_compile_features(ritardosensoreistruzione PRIVATE cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
