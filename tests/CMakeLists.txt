set(SOURCE
    labpack.c
)

link_directories(${CMAKE_BINARY_DIR}/src)
add_executable(labpack_tests ${SOURCE})
target_include_directories(labpack_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(labpack_tests ${OUTPUT_NAME})

