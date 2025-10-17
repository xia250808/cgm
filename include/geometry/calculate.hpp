#pragma once
#include "geometry/geo_core.hpp"

namespace cgm::geometry::calculate {

	template<typename T>
	T distance(Plane<T> plane, Point3<T> point) {
		return plane.normal_ * point - plane.distance_;
	}

}