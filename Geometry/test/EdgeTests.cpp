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

#include "catch.hpp"
#include "Edge.h"

using namespace TpaStarCpp::GeometryLibrary;

TEST_CASE("Edge should store passed argument")
{
    Vector a(1.0, 2.0);
    Vector b(3.0, 4.0);

    Edge e(a, b);

    CHECK(e.a().x() == Approx(1.0));
    CHECK(e.a().y() == Approx(2.0));
    CHECK(e.b().x() == Approx(3.0));
    CHECK(e.b().y() == Approx(4.0));
}

TEST_CASE("Distance from point should be zero if point falls on left endpoint")
{
    Vector a(2.0, 1.0);
    Vector b(4.0, 1.0);
    Vector pointToCheck(2.0, 1.0);
    Edge edge(a, b);

    CHECK(edge.distanceFrom(pointToCheck) == Approx(0.0));
}

TEST_CASE("Distance from point should be zero if point falls on right endpoint")
{
    Vector leftEndpoint(2.0, 1.0);
    Vector rightEndpoint(4.0, 1.0);
    Vector pointToCheck(4.0, 1.0);
    Edge edge(leftEndpoint, rightEndpoint);

    CHECK(edge.distanceFrom(pointToCheck) == Approx(0.0));
}

TEST_CASE("Distance from point should be zero if point falls on edge")
{
    Vector leftEndpoint(2.0, 1.0);
    Vector rightEndpoint(4.0, 1.0);
    Vector pointToCheck(3.0, 1.0);
    Edge edge(leftEndpoint, rightEndpoint);

    CHECK(edge.distanceFrom(pointToCheck) == Approx(0.0));
}

TEST_CASE("Distance of point from horizontal edge should be distance on y axis if point falls between endpoints on x axis")
{
    Vector leftEndpoint(2.0, 1.0);
    Vector rightEndpoint(4.0, 1.0);
    Vector pointToCheck(3.0, 2.5);
    Edge edge(leftEndpoint, rightEndpoint);

    CHECK(edge.distanceFrom(pointToCheck) == Approx(1.5));
}

TEST_CASE("Distance of point from horizontal edge should be distance from left endpoint if point falls left from left endpoint")
{
    Vector leftEndpoint(2.0, 1.0);
    Vector rightEndpoint(4.0, 1.0);
    Vector pointToCheck(1.0, 2.0);
    Edge edge(leftEndpoint, rightEndpoint);
    double squareRootTwo = 1.41421;

    CHECK(edge.distanceFrom(pointToCheck) == Approx(squareRootTwo));
}

TEST_CASE("Distance of point from horizontal edge should be distance from right endpoint if point falls right from right endpoint")
{
    Vector leftEndpoint(2.0, 1.0);
    Vector rightEndpoint(4.0, 1.0);
    Vector pointToCheck(6.0, 2.0);
    Edge edge(leftEndpoint, rightEndpoint);
    double squareRootFive = 2.23607;

    CHECK(edge.distanceFrom(pointToCheck) == Approx(squareRootFive));
}

TEST_CASE("Distance of point from diagonal edge should be the lenght of right line segment between edge and point")
{
    Vector leftEndpoint(1.0, 1.0);
    Vector rightEndpoint(3.0, 3.0);
    Vector pointToCheck(1.0, 3.0);
    double squareRootTwo = 1.41421;
    Edge edge(leftEndpoint, rightEndpoint);

    CHECK(edge.distanceFrom(pointToCheck) == Approx(squareRootTwo));
}

TEST_CASE("Points that are closer to the edge than vector tolerance should fall on edge")
{
    double tolerance = 0.00001;
    Vector a(0.0, 0.0);
    Vector b(1.0, 0.0);
    Edge edge(a, b);
    Vector pointToCheck(0.5, 0.000005);

    auto is_point_on_edge = edge.pointLiesOnEdge(pointToCheck);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK(is_point_on_edge);
}

TEST_CASE("Points that are exactly in vector tolerance distance should not fall on edge")
{
    double tolerance = 0.00001;
    Vector a(0.0, 0.0);
    Vector b(1.0, 0.0);
    Edge edge(a, b);
    Vector pointToCheck(0.5, 0.1);

    auto is_point_on_edge = edge.pointLiesOnEdge(pointToCheck);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK_FALSE(is_point_on_edge);
}

TEST_CASE("Edges should be equal if they lie between same endpoints")
{
    Vector leftEndpointOfFirstEdge(1.0, 3.0);
    Vector leftEndpointOfSecondEdge(1.0, 3.0);
    Vector rightEndpointOfFirstEdge(4.0, 3.0);
    Vector rightEndpointOfSecondEdge(4.0, 3.0);
    Edge firstEdge(leftEndpointOfFirstEdge, rightEndpointOfFirstEdge);
    Edge secondEdge(leftEndpointOfSecondEdge, rightEndpointOfSecondEdge);

    CHECK(firstEdge.equals(secondEdge));
}

TEST_CASE("EdgesShouldBeEqualIfTheyLieBetweenSameEndpointsIndependentlyFromEndpointOrder")
{
    Vector leftEndpointOfFirstEdge(1.0, 3.0);
    Vector leftEndpointOfSecondEdge(1.0, 3.0);
    Vector rightEndpointOfFirstEdge(4.0, 3.0);
    Vector rightEndpointOfSecondEdge(4.0, 3.0);
    Edge firstEdge(leftEndpointOfFirstEdge, rightEndpointOfFirstEdge);
    Edge secondEdge(rightEndpointOfSecondEdge, leftEndpointOfSecondEdge);

    CHECK(firstEdge.equals(secondEdge));
}

TEST_CASE("Edges should not be equal if one of their endpoints are different")
{
    Vector leftEndpointOfFirstEdge(5.0, 8.0);
    Vector leftEndpointOfSecondEdge(1.0, 3.0);
    Vector rightEndpointOfFirstEdge(4.0, 3.0);
    Vector rightEndpointOfSecondEdge(4.0, 3.0);
    Edge firstEdge(leftEndpointOfFirstEdge, rightEndpointOfFirstEdge);
    Edge secondEdge(rightEndpointOfSecondEdge, leftEndpointOfSecondEdge);

    CHECK_FALSE(firstEdge.equals(secondEdge));
}

TEST_CASE("Distorted edge should not be created")
{
    Vector a(0.0, 1.0);
    Vector b(0.0, 1.0);

    CHECK_THROWS_WITH(Edge(a, b), Catch::Contains("equal"));
}
