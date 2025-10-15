#pragma once
#include "geometry/geo_core.hpp"
#include <limits>

namespace cgm::geometry {

	template<typename T>
	class AABB3
	{
	public:
		Point3<T> min_;
		Point3<T> max_;

		T& minX() { return min_[0]; }
		const T& minX() const { return min_[0]; }

		T& minY() { return min_[1]; }
		const T& minY() const { return min_[1]; }

		T& minZ() { return min_[2]; }
		const T& minZ() const { return min_[2]; }

		T& maxX() { return max_[0]; }
		const T& maxX() const { return max_[0]; }

		T& maxY() { return max_[1]; }
		const T& maxY() const { return max_[1]; }

		T& maxZ() { return max_[2]; }
		const T& maxZ() const { return max_[2]; }

		AABB3();
		AABB3(const Point3<T>& min, const Point3<T>& max) : min_(min), max_(max) {};
		static AABB3<T> empty() {
			return AABB3<T>();
		};
		void print();
		void add(const Point3<T>& p);


	private:

	};

	template<typename T>
	AABB3<T>::AABB3()
		: min_(
			{
				std::numeric_limits<T>::max(),
				std::numeric_limits<T>::max(),
				std::numeric_limits<T>::max()
			}),
		max_(
			{
				std::numeric_limits<T>::lowest(),
				std::numeric_limits<T>::lowest(),
				std::numeric_limits<T>::lowest()
			}
		) {};

	template<typename T>
	void AABB3<T>::add(const Point3<T>& p) {
		if (minX() > p[0]) minX() = p[0];
		if (maxX() < p[0]) maxX() = p[0];
		if (minY() > p[1]) minY() = p[1];
		if (maxY() < p[1]) maxY() = p[1];
		if (minZ() > p[2]) minZ() = p[2];
		if (maxZ() < p[2]) maxZ() = p[2];
	}

	template<typename T>
	void AABB3<T>::print() {
		min_.print();
		max_.print();
	}
}