#pragma once
#include "geometry/geo_core.hpp"

namespace cgm::geometry {
	template<typename T>
	class LineSegment
	{
	public:
		Point3<T> org_;
		Point3<T> end_;
		LineSegment(const Point3<T>& org, const Point3<T>& end) :org_(org), end_(end) {};
		void print();
		T length();
		Vec<T, 3> direction()const;

	private:

	};
	template<typename T>
	inline void LineSegment<T>::print()
	{
		org_.print();
		end_.print();
	}

	template<typename T>
	inline T LineSegment<T>::length()
	{
		return (end_ - org_).length();
	}

	template<typename T>
	inline Vec<T, 3> LineSegment<T>::direction() const{
		return end_ - org_;
	}
}