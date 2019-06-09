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

#include <vector>
#include <memory>

namespace TpaStarCpp::GeometryLibrary {

    class TriangleSkeleton;
    class Triangle;
    class Vector;

    class TriangleGraph : public std::enable_shared_from_this<TriangleGraph> {

    private:
        std::vector<TriangleSkeleton> triangles_;
        std::vector<std::vector<long>> neighbourIds_;

        long determineIdOfTriangleUnderPoint(Vector point);
        Triangle buildTriangleFromId(long id);

    public:
        explicit TriangleGraph(std::vector<TriangleSkeleton> triangles);
        bool containsPoint(Vector point);
        Triangle getTriangleUnder(Vector point);
        std::vector<Triangle> getNeighbours(Triangle triangle);

    };

}