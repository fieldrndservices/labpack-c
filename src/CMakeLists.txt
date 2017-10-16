set(SOURCE 
    labpack.h
    labpack-status.c
    labpack-writer.c
    mpack.c
)

# Shared library build
add_library(shared SHARED ${SOURCE})
set_target_properties(shared PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
target_compile_definitions(shared PRIVATE LABPACK_BUILD_SHARED)

