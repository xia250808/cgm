#pragma once
#include "geometry/geo_core.hpp"

namespace cgm::geometry::calculate {

	template<typename T>
	T distance(Plane<T> plane, Point3<T> point) {
		return plane.normal_ * point - plane.distance_;
	}

	template<typename T>
	Vec3<T> barycentricCoordinates(const Triangle<T>& inTriangle,const Point3<T>& point) {
		return inTriangle.barycentric(point);
	}

}