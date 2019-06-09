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

    Triangle triangle(id, Vector(x_a, y_a), Vector(x_b, y_b), Vector(x_c, y_c), nullptr);

    CHECK(triangle.id() == id);
    CHECK(triangle.a().x() == Approx(x_a));
    CHECK(triangle.a().y() == Approx(y_a));
    CHECK(triangle.b().x() == Approx(x_b));
    CHECK(triangle.b().y() == Approx(y_b));
    CHECK(triangle.c().x() == Approx(x_c));
    CHECK(triangle.c().y() == Approx(y_c));
}
