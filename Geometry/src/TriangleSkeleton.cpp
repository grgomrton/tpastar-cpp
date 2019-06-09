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

#include <TriangleSkeleton.h>
#include <Edge.h>
#include <stdexcept>

using namespace TpaStarCpp::GeometryLibrary;

TriangleSkeleton::TriangleSkeleton(Vector a, Vector b, Vector c) : vertices_{a, b, c} {
    Edge ab(a, b);
    Edge ac(a, c);
    Edge bc(b, c);
    if (ab.pointLiesOnEdge(c) || ac.pointLiesOnEdge(b) || bc.pointLiesOnEdge(a))
    {
        throw std::invalid_argument("Distorted triangles are not supported");
    }
}

int TriangleSkeleton::sharedVertexCountWith(TriangleSkeleton other)
{
    int result = 0;
    for (auto other_vertex : other.vertices_) {
        if (matchesAnyStoredVertex(other_vertex)) {
            result++;
        }
    }
    return result;
}

bool TriangleSkeleton::matchesAnyStoredVertex(Vector point)
{
    return ((point == vertices_[0]) || (point == vertices_[1]) || (point == vertices_[2]));
}

bool TriangleSkeleton::isAdjacentWith(TriangleSkeleton other) { return sharedVertexCountWith(other) == 2; }

Vector TriangleSkeleton::a() { return vertices_[0]; }

Vector TriangleSkeleton::b() { return vertices_[1]; }

Vector TriangleSkeleton::c() { return vertices_[2]; }

bool TriangleSkeleton::containsPoint(Vector point)
{
    // source: http://www.blackpawn.com/texts/pointinpoly/default.html
    // Compute vectors
    auto v0 = c() - a(); // v0 = C - A
    auto v1 = b() - a(); // v1 = B - A
    auto v2 = point - a(); // v2 = P - A

    // Lower bounds taking into consideration vector equality check parameters
    double boundaryWidth = Vector::EQUALITY_CHECK_TOLERANCE;
    double lowU = boundaryWidth / v0.len();
    double lowV = boundaryWidth / v1.len();

    // Compute dot products
    double dot00 = v0.dotProductWith(v0); // dot00 = dot(v0, v0)
    double dot01 = v0.dotProductWith(v1); // dot01 = dot(v0, v1)
    double dot02 = v0.dotProductWith(v2); // dot02 = dot(v0, v2)
    double dot11 = v1.dotProductWith(v1); // dot11 = dot(v1, v1)
    double dot12 = v1.dotProductWith(v2); // dot12 = dot(v1, v2)

    // Compute barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01); // invDenom = 1 / (dot00 * dot11 - dot01 * dot01)
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom; // u = (dot11 * dot02 - dot01 * dot12) * invDenom
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom; // v = (dot00 * dot12 - dot01 * dot02) * invDenom

    // Check if point is in triangle
    // The higher bound is increased by the applicable border size for the u and v weights
    return (u > -lowU) && (v > -lowV) &&
           (u + v < 1.0 + lowU * u + lowV * v); // return (u >= 0) && (v >= 0) && (u + v < 1)
}