set(SOURCES
    status.c
    writer.c
)

include_directories(${labpack_SOURCE_DIR}/src)
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

foreach(SOURCE ${SOURCES})
    get_filename_component(NAME ${SOURCE} NAME_WE)
    add_executable(${NAME} ${SOURCE})
    target_link_libraries(${NAME} ${OUTPUT_NAME})
    add_dependencies(${NAME} shared)
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach(SOURCE)

