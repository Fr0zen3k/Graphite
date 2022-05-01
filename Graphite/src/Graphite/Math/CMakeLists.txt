set(
        MATH_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/BoundingBox.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/BoundingSphere.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Plane.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/StraightLine.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Transform.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ViewFrustum.cpp"
        CACHE INTERNAL "" FORCE
)

set(
        MATH_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/BoundingBox.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/BoundingSphere.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Plane.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/StraightLine.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Transform.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ViewFrustum.h"
        CACHE INTERNAL  "" FORCE
)