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

#include "Vector.h"

namespace TpaStarCpp::GeometryLibrary {

    class TriangleSkeleton {

    private:
        const Vector vertices_[3];

        bool matchesAnyStoredVertex(Vector point);
        int sharedVertexCountWith(TriangleSkeleton other);

    public:
        TriangleSkeleton(Vector a,Vector b, Vector c);
        bool isAdjacentWith(TriangleSkeleton other);
        bool containsPoint(Vector point);
        Vector a();
        Vector b();
        Vector c();

    };

}