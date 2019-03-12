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
#include "Vector.h"

using namespace TpaStarCpp::GeometryLibrary;

TEST_CASE("Vector should store passed argument")
{
    double x = 1.0;
    double y = 2.0;

    Vector v(x, y);
    auto x_acquired = v.x();
    auto y_acquired = v.y();

    CHECK(x_acquired == Approx(1.0));
    CHECK(y_acquired == Approx(2.0));
}

TEST_CASE("Addition should not change input parameters")
{
    Vector v1(2.0, 3.0);
    Vector v2(2.0, -2.0);

    v1 + v2;

    CHECK(v1.x() == Approx(2.0));
    CHECK(v1.y() == Approx(3.0));
    CHECK(v2.x() == Approx(2.0));
    CHECK(v2.y() == Approx(-2.0));
}

TEST_CASE("Scalar multiplication should increase its' components in the same magnitude")
{
    Vector v(2.0, 5.0);

    auto result = v * 3.0;

    CHECK(result.x() == Approx(6.0));
    CHECK(result.y() == Approx(15.0));
}

// values come from examples on www.onlinemathlearning.com
TEST_CASE("Adding another vector should result in new vector containg sum of corresponding coordinate values") // todo containing
{
    Vector v1(2.0, 3.0);
    Vector v2(2.0, -2.0);

    auto v1_plus_v2 = v1 + v2;

    CHECK(v1_plus_v2.x() == Approx(4.0));
    CHECK(v1_plus_v2.y() == Approx(1.0));
}

// values come from examples on www.onlinemathlearning.com
TEST_CASE("Subtracting another vector should result in new vector containing coordinates subtracted the second one from the first")
{
    Vector v1(2.0, 1.0);
    Vector v2(3.0, -2.0);

    auto v1_minus_v2 = v1 - v2;

    CHECK(v1_minus_v2.x() == Approx(-1.0));
    CHECK(v1_minus_v2.y() == Approx(3.0));
}

TEST_CASE("Distance of two vectors should be their cartesian distance in two dimension")
{
    Vector v1(1.0, 1.0);
    Vector v2(2.0, 2.0);
    double square_root_two = 1.41421;

    auto distance = v1.distanceFrom(v2);

    CHECK(distance == Approx(square_root_two));
}

TEST_CASE("Distance of two vectors should be independent from order")
{
    Vector v1(1.0, 1.0);
    Vector v2(2.0, 2.0);
    double square_root_two = 1.41421;

    auto distance = v2.distanceFrom(v1);

    CHECK(distance == Approx(square_root_two));
}

TEST_CASE("Vector distance from itself should be zero")
{
    Vector v2(2.0, 2.0);

    auto distance = v2.distanceFrom(v2);

    CHECK(distance == Approx(0.0));
}

TEST_CASE("Unit vector in clockwise direction should be determined as clockwise")
{
    Vector u(0.0, 1.0);
    Vector v(1.0, 0.0);

    CHECK(v.isInClockWiseDirectionFrom(u));
}

TEST_CASE("Unit vector in counter clockwise direction should be determined as counter clockwise")
{
    Vector u(0.0, 1.0);
    Vector v(-1.0, 0.0);

    CHECK(v.isInCounterClockWiseDirectionFrom(u));
}

TEST_CASE("Unit vector in counter clockwise direction should not be determined as clockwise")
{
    Vector u(0.0, 1.0);
    Vector v(-1.0, 0.0);

    CHECK_FALSE(v.isInClockWiseDirectionFrom(u));
}

TEST_CASE("Unit vector in clockwise direction should not be determined as counter clockwise")
{
    Vector u(0.0, 1.0);
    Vector v(1.0, 0.0);

    CHECK_FALSE(v.isInCounterClockWiseDirectionFrom(u));
}

TEST_CASE("Parallel vectors should be determined clockwise")
{
    Vector p1(1.0, 1.0);
    Vector p2(3.0, 1.0);
    Vector pm(2.0, 1.0);
    Vector pm_to_p1 = p1 - pm;
    Vector pm_to_p2 = p2 - pm;

    CHECK(pm_to_p1.isInClockWiseDirectionFrom(pm_to_p2));
}

TEST_CASE("Parallel vectors should be determined counter clockwise")
{
    Vector p1(1.0, 1.0);
    Vector p2(3.0, 1.0);
    Vector pm(2.0, 1.0);
    Vector pm_to_p1 = p1 - pm;
    Vector pm_to_p2 = p2 - pm;

    CHECK(pm_to_p1.isInCounterClockWiseDirectionFrom(pm_to_p2));
}

TEST_CASE("Vectors in counter clockwise orientation should be determined as counter clockwise") // todo clockwise
{
    Vector p2(3.0, 1.0);
    Vector p1(2.0, 2.0);
    Vector pm(2.0, 1.0);
    Vector pm_to_p1 = p1 - pm;
    Vector pm_to_p2 = p2 - pm;

    CHECK(pm_to_p2.isInClockWiseDirectionFrom(pm_to_p1));
}

TEST_CASE("Vectors in clockwise orientation should be determined as clockwise")
{
    Vector p2(3.0, 1.0);
    Vector p1(2.0, 2.0);
    Vector pm(2.0, 1.0);
    Vector pm_to_p1 = p1 - pm;
    Vector pm_to_p2 = p2 - pm;

    CHECK(pm_to_p1.isInCounterClockWiseDirectionFrom(pm_to_p2));
}

TEST_CASE("Two vectors representing exactly the same point should be equal")
{
    Vector u(2.5, 3.6);
    Vector v(2.5, 3.6);

    CHECK(u == v);
}

TEST_CASE("Two vectors representing exactly the same point should be equal independently from comparison order")
{
    Vector u(2.5, 3.6);
    Vector v(2.5, 3.6);

    CHECK(v == u);
}

TEST_CASE("Vector should be equal to itself")
{
    Vector u(2.5, 3.5);

    CHECK(u == u);
}

TEST_CASE("Vectors differing less than the tolerance should be equal")
{
    double tolerance = 0.00001;
    Vector u(1.0, 1.0);
    Vector v(1.000005, 1.0);

    auto result = (u == v);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK(result);
}

TEST_CASE("Vectors differing exactly the same amount as the tolerance should not be equal")
{
    double tolerance = 0.00001;
    Vector u(1.0, 1.0);
    Vector v(1.00001, 1.0);

    auto result = (u == v);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK_FALSE(result);
}

TEST_CASE("Vectors differing more than the tolerance should not be equal")
{
    double tolerance = 0.00001;
    Vector u(1.01, 1.01);
    Vector v(1.0, 1.0);

    auto result = (u == v);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK_FALSE(result);
}

TEST_CASE("Vectors differing in both coordinates but are closer than tolerance should be equal")
{
    double tolerance = 0.00001;
    Vector u(1.000001, 1.0);
    Vector v(1.0, 1.000001);

    auto result = (u == v);

    CHECK(Vector::EQUALITY_CHECK_TOLERANCE == Approx(tolerance));
    CHECK(result);
}

//[Test] // todo this is uninterpretable here. is there any place where we build upon this behaviour?
//public void EqualsShouldWorkWithNullParameter()
//{
//    var vector = new Vector(1.0, 0.0);
//
//    Action gettingEqualsWithNull = () => vector.Equals(null);
//
//    gettingEqualsWithNull.ShouldNotThrow();
//}