#pragma once
#include "geometry/geo_core.hpp"

namespace cgm::geometry {
	template<typename T>
	class LineSegment
	{
	public:
		Point3<T> pOrg_;
		Point3<T> pEnd_;
		LineSegment(const Point3<T>& org, const Point3<T>& end) :pOrg_(org), pEnd_(end) {};
		void print();
		T length();

	private:

	};
	template<typename T>
	inline void LineSegment<T>::print()
	{
		pOrg_.print();
		pEnd_.print();
	}

	template<typename T>
	inline T LineSegment<T>::length()
	{
		return (pEnd_ - pOrg_).length();
	}
}