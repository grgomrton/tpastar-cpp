/**
 * Copyright 2019 Márton Gergó
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <catch.hpp>
#include <Triangle.h>
#include "TriangleGraph.h"
#include "TriangleSkeleton.h"

using namespace TpaStarCpp::GeometryLibrary;


class TestTriangle {
    std::vector<Vector> vertices_;

public:
    TestTriangle(Vector a, Vector b, Vector c) {
        vertices_ = std::vector<Vector> { a, b, c };
    }
    bool matches(Triangle triangle) {
        auto otherVertices = std::vector<Vector> { triangle.a(), triangle.b(), triangle.c() };
        bool matches = true;
        for (auto vertex : vertices_) {
            matches &= std::any_of(
                    otherVertices.begin(),
                    otherVertices.end(),
                    [&](auto otherVertex) { return vertex == otherVertex; });
        }
        return matches;
    }
};


TEST_CASE("Test triangle should match two triangles independently from point definiton order")
{
    Triangle result(1, Vector(1.0, 4.0), Vector(3.0, 4.0), Vector(3.0, 2.0), nullptr);
    TestTriangle testTriangle(Vector(3.0, 2.0), Vector(1.0, 4.0), Vector(3.0, 4.0));

    CHECK(testTriangle.matches(result));
}

TEST_CASE("Test triangle should detect non-overlapping triangles")
{
    Triangle result(1, Vector(1.0, 4.0), Vector(3.0, 4.0), Vector(3.0, 2.0), nullptr);
    TestTriangle testTriangle(Vector(3.0, 2.0), Vector(1.0, 4.1), Vector(3.0, 4.0));

    CHECK_FALSE(testTriangle.matches(result));
}

TEST_CASE("Triangle graph should be possible to instantiate with triangle skeleton")
{
    auto triangles = std::vector<TriangleSkeleton> { TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)) };

    auto graph = std::make_shared<TriangleGraph>(triangles);
}

TEST_CASE("Triangle graph should be able to determine whether a point contained by any triangle")
{
    auto triangles = std::vector<TriangleSkeleton> { TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)) };
    auto graph = std::make_shared<TriangleGraph>(triangles);

    CHECK(graph->containsPoint(Vector(1.5, 2.5)));
}

TEST_CASE("Triangle graph should determine an outlier point")
{
    auto triangles = std::vector<TriangleSkeleton> { TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)) };
    auto graph = std::make_shared<TriangleGraph>(triangles);

    CHECK_FALSE(graph->containsPoint(Vector(0.0, 2.5)));
}


TEST_CASE("Graph should determine the triangle that lies under the specified point")
{
    auto triangles = std::vector<TriangleSkeleton> { TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)) };
    auto graph = std::make_shared<TriangleGraph>(triangles);
    auto startPoint = Vector(1.5, 2.5);
    auto testTriangle = TestTriangle(Vector(1.0, 4.0), Vector(3.0, 2.0), Vector(1.0, 2.0));

    auto startTriangle = graph->getTriangleUnder(startPoint);

    CHECK(testTriangle.matches(startTriangle));
}

TEST_CASE("Graph should throw exception if triangle is expected to be acquired for an outlier point")
{
    auto triangles = std::vector<TriangleSkeleton> { TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)) };
    auto graph = std::make_shared<TriangleGraph>(triangles);
    auto startPoint = Vector(0.0, 2.5);

    CHECK_THROWS(graph->getTriangleUnder(startPoint), Catch::Contains("cannot", Catch::CaseSensitive::No));
}

TEST_CASE("Triangles in a square should have exactly one neighbour")
{
    auto triangles = std::vector<TriangleSkeleton> {
        TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)),
        TriangleSkeleton(Vector(3.0, 4.0), Vector(3.0, 2.0), Vector(1.0, 4.0)),
    };
    auto graph = std::make_shared<TriangleGraph>(triangles);
    auto startPoint = Vector(1.5, 2.5);
    auto neighbourTriangleMathcer = TestTriangle(Vector(3.0, 4.0), Vector(3.0, 2.0), Vector(1.0, 4.0));

    auto startTriangle = graph->getTriangleUnder(startPoint);
    auto neighbours = startTriangle.getNeighbours();

    CHECK(neighbours.size() == 1);
    CHECK(neighbourTriangleMathcer.matches(neighbours[0]));
}

TEST_CASE("Neighbour triangle in a square should have exactly one neighbour")
{
    auto triangles = std::vector<TriangleSkeleton> {
            TriangleSkeleton(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0)),
            TriangleSkeleton(Vector(3.0, 4.0), Vector(3.0, 2.0), Vector(1.0, 4.0)),
    };
    auto graph = std::make_shared<TriangleGraph>(triangles);
    auto startPoint = Vector(2.5, 3.5);
    auto neighbourTriangleMathcer = TestTriangle(Vector(1.0, 2.0), Vector(3.0, 2.0), Vector(1.0, 4.0));

    auto startTriangle = graph->getTriangleUnder(startPoint);
    auto neighbours = startTriangle.getNeighbours();

    CHECK(neighbours.size() == 1);
    CHECK(neighbourTriangleMathcer.matches(neighbours[0]));
}