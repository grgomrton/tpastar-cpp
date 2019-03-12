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
#include "Triangle.h"

using namespace TpaStarCpp::GeometryLibrary;

TEST_CASE("Triangle should store the passed arguments")
{
    long id = 1;
    double x_a = 1.0;
    double y_a = 1.0;
    double x_b = 2.0;
    double y_b = 1.0;
    double x_c = 1.5;
    double y_c = 2.0;

    Triangle triangle(id, Vector(x_a, y_a), Vector(x_b, y_b), Vector(x_c, y_c));

    CHECK(triangle.id() == id);
    CHECK(triangle.a().x() == Approx(x_a));
    CHECK(triangle.a().y() == Approx(y_a));
    CHECK(triangle.b().x() == Approx(x_b));
    CHECK(triangle.b().y() == Approx(y_b));
    CHECK(triangle.c().x() == Approx(x_c));
    CHECK(triangle.c().y() == Approx(y_c));
}

TEST_CASE("Distorted triangles should not be created when third corner lies on edge between first and second corner")
{
    long id = 0;
    Vector a(2.0, 2.0);
    Vector b(3.0, 1.0);
    Vector c(2.5, 1.5);

    CHECK_THROWS_WITH(Triangle(id, a, b, c), Catch::Contains("distorted", Catch::CaseSensitive::No));
}

TEST_CASE("Distorted triangles should not be created when second corner lies on edge between first and third corner")
{
    long id = 0;
    Vector a(2.0, 2.0);
    Vector b(4.0, 4.0);
    Vector c(3.0, 3.0);

    CHECK_THROWS_WITH(Triangle(id, a, b, c), Catch::Contains("distorted", Catch::CaseSensitive::No));
}

TEST_CASE("Distorted triangles should not be created when first corner lies on edge between second and third corner")
{
    long id = 0;
    Vector a(3.0, 3.0);
    Vector b(4.0, 4.0);
    Vector c(2.0, 2.0);

    CHECK_THROWS_WITH(Triangle(id, a, b, c), Catch::Contains("distorted", Catch::CaseSensitive::No));
}

TEST_CASE("Distorted triangles should not be created when two corners overlap each-other")
{
    long id = 0;
    Vector a(1.0, 1.0);
    Vector b(3.0, 3.0);
    Vector c(1.0, 1.0);

    CHECK_THROWS_WITH(Triangle(id, a, b, c), Catch::Contains("endpoints", Catch::CaseSensitive::No));
}

TEST_CASE("Non-adjacent triangles should be determined not neighbours")
{
    Triangle t1(1, Vector(1.0, 1.0), Vector(2.0, 1.0), Vector(2.0, 3.0));
    Triangle t2(10, Vector(4.0, 5.0), Vector(6.0, 5.0), Vector(5.0, 3.0));

    CHECK_FALSE(t1.isAdjacentWith(t2));
}

TEST_CASE("Adjacent triangles should be determined neighbours")
{
    Triangle t1(1, Vector(1.0, 1.0), Vector(2.0, 1.0), Vector(2.0, 3.0));
    Triangle t2(10, Vector(2.0, 1.0), Vector(2.0, 3.0), Vector(5.0, 1.0));

    CHECK(t1.isAdjacentWith(t2));
}

TEST_CASE("Adjacent triangles should be determined neighbours independently from query order")
{
    Triangle t1(1, Vector(1.0, 1.0), Vector(2.0, 1.0), Vector(2.0, 3.0));
    Triangle t2(10, Vector(2.0, 1.0), Vector(2.0, 3.0), Vector(5.0, 1.0));

    CHECK(t2.isAdjacentWith(t1));
}

TEST_CASE("Adjacent triangles should be determined neighbours independently from corner definition direction")
{
    Triangle t1(1, Vector(1.0, 1.0), Vector(2.0, 1.0), Vector(2.0, 3.0));
    Triangle t2(10, Vector(5.0, 1.0), Vector(2.0, 3.0), Vector(2.0, 1.0));

    CHECK(t2.isAdjacentWith(t1));
}

TEST_CASE("Triangles that are connected by only one corner should not be determined neighbours")
{
    Triangle t1(1, Vector(1.0, 1.0), Vector(2.0, 1.0), Vector(2.0, 3.5));
    Triangle t2(10, Vector(2.0, 1.0), Vector(5.0, 1.0), Vector(2.0, 3.0));

    CHECK_FALSE(t1.isAdjacentWith(t2));
}