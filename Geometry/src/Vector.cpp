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

#include <Vector.h>
#include <cmath>

using namespace TpaStarCpp::GeometryLibrary;


Vector::Vector(double x, double y) : x(x), y(y) { }

double Vector::getX() { return x; }

double Vector::getY() { return y; }

Vector Vector::plus(Vector other) { return Vector(x + other.x, y + other.y); }

Vector Vector::minus(Vector other) { return Vector(x - other.x, y - other.y); }

double Vector::distanceFrom(Vector other) { return (*this).minus(other).len(); }

Vector Vector::times(double scalar) { return Vector(scalar * x, scalar * y); }

bool Vector::isInClockWiseDirectionFrom(Vector other) { return zComponentOfCrossProductWith(other) >= 0.0; }

bool Vector::isInCounterClockWiseDirectionFrom(Vector other) { return zComponentOfCrossProductWith(other) <= 0.0; }

bool Vector::equals(Vector other) { return (*this).distanceFrom(other) < EQUALITY_CHECK_TOLERANCE; }

double Vector::len() { return sqrt(pow(x, 2.0) + pow(y, 2.0)); }

double Vector::zComponentOfCrossProductWith(Vector other) { return x * other.y - y * other.x; }
