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

#include <TriangleGraph.h>
#include <algorithm>
#include <stdexcept>
#include "Vector.h"
#include "TriangleSkeleton.h"
#include "Triangle.h"

using namespace TpaStarCpp::GeometryLibrary;

TriangleGraph::TriangleGraph(std::vector<TriangleSkeleton> triangles) :
    triangles_(std::move(triangles)),
    neighbourIds_(std::vector<std::vector<long>>(triangles_.size()))
{
    for (long i=0; i<triangles_.size(); i++) {
        for (long j=0; j<triangles_.size(); j++) {
            if (triangles_[i].isAdjacentWith(triangles_[j])) {
                neighbourIds_[i].push_back(j);
            }
        }
    }
}

std::vector<Triangle> TriangleGraph::getNeighbours(Triangle triangle) {
    if ((triangle.id() > triangles_.size()) || (triangle.id() < 0))
    {
        throw std::invalid_argument("Cannot find triangle with the specified id");
    }
    // todo check input Triangle equality with stored one
    std::vector<Triangle> adjacentTriangles;
    auto neighbourIds = neighbourIds_[triangle.id()];
    std::for_each(begin(neighbourIds), end(neighbourIds),
            [&](auto& id) { adjacentTriangles.push_back(buildTriangleFromId(id)); });
    return adjacentTriangles;
}

bool TriangleGraph::containsPoint(Vector point) {
    return std::any_of(begin(triangles_), end(triangles_), [&](auto& t) { return t.containsPoint(point); });
}

Triangle TriangleGraph::getTriangleUnder(Vector point) {
    if (!containsPoint(point))
    {
        throw std::invalid_argument("The specified point is not contained by any triangle in this graph");
    }
    auto id = determineIdOfTriangleUnderPoint(point);
    return buildTriangleFromId(id);
}

long TriangleGraph::determineIdOfTriangleUnderPoint(Vector point) {
    for (long i=0; i<triangles_.size(); i++) {
        if (triangles_[i].containsPoint(point)) {
            return i;
        }
    }
    throw std::invalid_argument("Cannot find triangle under the specified point");
}

Triangle TriangleGraph::buildTriangleFromId(long id) {
    auto skeleton = triangles_[id];
    return Triangle(id, skeleton.a(), skeleton.b(), skeleton.c(), shared_from_this());
}
