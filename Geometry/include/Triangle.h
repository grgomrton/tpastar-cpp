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

    class Triangle {

    private:
        const long id_;
        const Vector vertices_[3];

        bool matchesAnyStoredVertex(Vector point) const;
        int sharedVertexCountWith(Triangle other) const;

    public:
        Triangle(long id, Vector a,Vector b, Vector c);
        Vector a() const;
        Vector b() const;
        Vector c() const;
        long id() const;
        bool isAdjacentWith(Triangle other) const;

    };

}