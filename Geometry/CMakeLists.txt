add_library(GeometryLibrary include/Vector.h src/Vector.cpp)
target_include_directories(GeometryLibrary PUBLIC include)

add_executable(GeometryTests test/include/catch.hpp test/VectorTest.cpp)
target_include_directories(GeometryTests PRIVATE test/include)
target_link_libraries(GeometryTests GeometryLibrary)