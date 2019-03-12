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

Vector::Vector(double x, double y) : x_(x), y_(y) { }

double Vector::x() const { return x_; }

double Vector::y() const { return y_; }

Vector Vector::operator+(Vector other) const { return Vector(x_ + other.x_, y_ + other.y_); }

Vector Vector::operator-(Vector other) const { return Vector(x_ - other.x_, y_ - other.y_); }

double Vector::distanceFrom(Vector other) const { return ((*this) - other).len(); }

Vector Vector::operator*(double scalar) const { return Vector(scalar * x_, scalar * y_); }

bool Vector::isInClockWiseDirectionFrom(Vector other) const { return zComponentOfCrossProductWith(other) >= 0.0; }

bool Vector::isInCounterClockWiseDirectionFrom(Vector other) const { return zComponentOfCrossProductWith(other) <= 0.0; }

bool Vector::operator==(Vector other) const { return (*this).distanceFrom(other) < EQUALITY_CHECK_TOLERANCE; }

double Vector::len() const { return sqrt(pow(x_, 2.0) + pow(y_, 2.0)); }

double Vector::zComponentOfCrossProductWith(Vector other) const { return x_ * other.y_ - y_ * other.x_; }
