set(
        EVENT_CORE_SOURCES
        CACHE INTERNAL "" FORCE
)

set(
        EVENT_CORE_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/AppEvent.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ControllerEvent.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/EventCore.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Events.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/KeyEvent.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.h"
        CACHE INTERNAL  "" FORCE
)