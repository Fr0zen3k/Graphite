add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Profiling")

set(
        BENCHMARKING_SOURCES
        "${PROFILING_SOURCES}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Benchmarker.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/CsvLogger.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        BENCHMARKING_HEADERS
        "${PROFILING_HEADERS}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Benchmarker.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/CsvLogger.h"
        CACHE INTERNAL  "" FORCE
)