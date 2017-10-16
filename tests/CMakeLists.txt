set(SOURCE
    labpack-writer.c
)

set(TEST_TARGET_NAME test_${CMAKE_PROJECT_NAME})

include_directories(${labpack_SOURCE_DIR}/src)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_executable(${TEST_TARGET_NAME} ${SOURCE})
target_link_libraries(${TEST_TARGET_NAME} ${OUTPUT_NAME})
add_dependencies(${TEST_TARGET_NAME} shared)

add_test(NAME LabPackTests COMMAND ${TEST_TARGET_NAME})
