set(
        PROFILING_SOURCES
        "${PROFILING_SOURCES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tracker_RAM.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tracker_vRAM.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        PROFILING_HEADERS
        "${PROFILING_HEADERS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Timer.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tracker_RAM.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tracker_vRAM.h"
        CACHE INTERNAL  "" FORCE
)