add_library(GeometryLibrary include/Vector.h src/Vector.cpp src/Edge.cpp include/Edge.h src/Triangle.cpp include/Triangle.h)
target_include_directories(GeometryLibrary PUBLIC include)

add_executable(GeometryTests test/include/catch.hpp test/VectorTest.cpp test/EdgeTests.cpp test/Init.cpp test/TriangleTests.cpp)
target_include_directories(GeometryTests PRIVATE test/include)
target_link_libraries(GeometryTests GeometryLibrary)