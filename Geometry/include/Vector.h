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

#pragma once

namespace TpaStarCpp::GeometryLibrary {

    class Vector {

    private:
        const double x;
        const double y;

        double len();

        double zComponentOfCrossProductWith(Vector other);

    public:
        static constexpr double EQUALITY_CHECK_TOLERANCE = 0.00001;

        Vector(double x, double y);

        double getX();

        double getY();

        Vector plus(Vector other);

        Vector minus(Vector other);

        Vector times(double scalar);

        double distanceFrom(Vector other);

        bool isInCounterClockWiseDirectionFrom(Vector other);

        bool isInClockWiseDirectionFrom(Vector other);

        bool equals(Vector other);

    };

}