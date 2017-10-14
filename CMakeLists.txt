cmake_minimum_required(VERSION 3.9)
project(labpack VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_VISIBILITY_PRESET hidden)

if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    set(OUTPUT_NAME ${CMAKE_PROJECT_NAME}-x64)
else()
    set(OUTPUT_NAME ${CMAKE_PROJECT_NAME})
endif()

add_subdirectory(src)
