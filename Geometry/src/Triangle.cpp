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
#include "TriangleGraph.h"

using namespace TpaStarCpp::GeometryLibrary;

Triangle::Triangle(long id, Vector a, Vector b, Vector c, std::shared_ptr<TriangleGraph> graph) :
        id_(id), vertices_{a, b, c}, graph_(std::move(graph)) { }

Vector Triangle::a() { return vertices_[0]; }

Vector Triangle::b() { return vertices_[1]; }

Vector Triangle::c() { return vertices_[2]; }

long Triangle::id() { return id_; }

std::vector<Triangle> Triangle::getNeighbours() { return graph_->getNeighbours(*this); }
