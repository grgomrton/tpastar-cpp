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

#include <Triangle.h>
#include <Edge.h>
#include <stdexcept>

using namespace TpaStarCpp::GeometryLibrary;

Triangle::Triangle(long id, Vector a, Vector b, Vector c) : id_(id), vertices_{a, b, c}
{
    Edge ab(a, b);
    Edge ac(a, c);
    Edge bc(b, c);
    if (ab.pointLiesOnEdge(c) || ac.pointLiesOnEdge(b) || bc.pointLiesOnEdge(a))
    {
        throw std::invalid_argument("Distorted triangles are not supported");
    }
}

Vector Triangle::a() const { return vertices_[0]; }

Vector Triangle::b() const { return vertices_[1]; }

Vector Triangle::c() const { return vertices_[2]; }

long Triangle::id() const { return id_; }

int Triangle::sharedVertexCountWith(Triangle other) const
{
    int result = 0;
    for (auto other_vertex : other.vertices_) {
        if (matchesAnyStoredVertex(other_vertex)) {
            result++;
        }
    }
    return result;
}

bool Triangle::matchesAnyStoredVertex(Vector point) const
{
    return ((point == vertices_[0]) || (point == vertices_[1]) || (point == vertices_[2]));
}

bool Triangle::isAdjacentWith(Triangle other) const { return sharedVertexCountWith(other) == 2; }
