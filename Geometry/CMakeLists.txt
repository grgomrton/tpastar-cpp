add_library(GeometryLibrary
        src/Vector.cpp
        include/Vector.h
        src/Edge.cpp
        include/Edge.h
        src/Triangle.cpp
        include/Triangle.h
        src/TriangleSkeleton.cpp
        include/TriangleSkeleton.h
        src/TriangleGraph.cpp
        include/TriangleGraph.h)
target_include_directories(GeometryLibrary PUBLIC include)

add_executable(GeometryTests
        test/include/catch.hpp
        test/VectorTest.cpp
        test/EdgeTests.cpp
        test/Init.cpp
        test/TriangleTests.cpp
        test/TriangleSkeletonTests.cpp
        test/TriangleGraphTest.cpp)
target_include_directories(GeometryTests PRIVATE test/include)
target_link_libraries(GeometryTests GeometryLibrary)