# distance_sensor/CMakeLists.txt

add_library(distance_sensor STATIC
    DistanceSensor.hpp
    UltrasonicSensor.cpp
    UltrasonicSensor.hpp
    InfraredSensor.hpp
    InfraredSensor.cpp
)

target_compile_options(distance_sensor PRIVATE -Wall -pthread)
target_link_libraries(distance_sensor PRIVATE pigpio rt)

target_include_directories(distance_sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})