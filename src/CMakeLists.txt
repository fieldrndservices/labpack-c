set(SOURCE 
    labpack.c
    labpack.h
    labpack-reader.c
    labpack-status.c
    labpack-writer.c
    mpack.c
)

# Turn off Debug mode for mpack on Release configuration. This only works for
# MSVC, which supports multi-configuration builds.
set(CMAKE_C_FLAGS_RELEASE "-DMPACK_DEBUG=0")

# Shared library build
add_library(shared SHARED ${SOURCE})
set_target_properties(shared PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
target_compile_definitions(shared PRIVATE LABPACK_BUILD_SHARED)

