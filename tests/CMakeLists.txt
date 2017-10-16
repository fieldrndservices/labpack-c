set(SOURCE
    labpack.c
)

include_directories(${labpack_SOURCE_DIR}/src)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(labpack_tests ${SOURCE})
target_link_libraries(labpack_tests ${OUTPUT_NAME})
add_dependencies(labpack_tests shared)

add_test(NAME LabPackTests COMMAND labpack_tests)
