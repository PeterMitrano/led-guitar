project(led-guitar)
cmake_minimum_required(VERSION 3.0)

set(sfml_libs sfml-graphics sfml-window sfml-system sfml-audio)

add_executable(main main.cpp Adafruit_NeoPixel.cpp Arduino.cpp)
target_link_libraries(main ${sfml_libs})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
