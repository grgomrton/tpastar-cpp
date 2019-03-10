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

#include <Edge.h>
#include <algorithm>

using namespace TpaStarCpp::GeometryLibrary;

Edge::Edge(Vector a, Vector b) : a_(a), b_(b) {}

Vector Edge::a() { return a_; }

Vector Edge::b() { return b_; }

double Edge::distanceFrom(Vector point) { return this->closestPointTo(point).distanceFrom(point); }

/*
 * source: http://www.gamedev.net/topic/444154-closest-point-on-a-line/
 *
 * Vector GetClosetPoint(Vector A, Vector B, Vector P, bool segmentClamp) {
 *   //segmentClamp = true
 *   Vector AP = P - A:
 *   Vector AB = B - A;
 *   float ab2 = AB.x*AB.x + AB.y*AB.y;
 *   float ap_ab = AP.x*AB.x + AP.y*AB.y;
 *   float t = ap_ab / ab2;
 *   if (segmentClamp) {
 *     if (t < 0.0f) t = 0.0f;
 *     else if (t > 1.0f) t = 1.0f;
 *   }
 *   Vector Closest = A + AB * t;
 * }
 *
 */
Vector Edge::closestPointTo(Vector point)
{
    Vector ap = point.minus(a());
    Vector ab = b().minus(a());
    auto ab2 = ab.x() * ab.x() + ab.y() * ab.y();
    auto ap_ab = ap.x() * ab.x() + ap.y() * ab.y();
    auto t = ap_ab / ab2; // todo ab2 would be zero on a zero length edge in the origin, therefore exception is required in the ctor
    t = std::max(std::min(t, 1.0), 0.0);
    Vector closest = a().plus(ab.times(t));

    return closest;
}
