set(SOURCE 
    labpack-status.c
    labpack-writer.c
    mpack.c
)

add_library(shared SHARED ${SOURCE})
add_library(static STATIC ${SOURCE})
set_target_properties(shared PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
set_target_properties(static PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

