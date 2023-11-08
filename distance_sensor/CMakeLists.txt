# distance_sensor/CMakeLists.txt

add_library(distance_sensor STATIC
    UltrasonicSensor.cpp
    UltrasonicSensor.hpp
    DistanceSensor.hpp
    InfraredSensor.hpp
    InfreredSensor.cpp
)

target_include_directories(distance_sensor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})