#pragma once
#include "geometry/geo_core.hpp"

namespace cgm::geometry {

	template<typename T>
	class Plane
	{
	public:
		Vec<T, 3> normal_;
		T d_;
		Plane();
		Plane(const Point3<T> p1, const Point3<T> p2, const Point3<T> p3);
		void print();
		~Plane();

	private:

	};

	template<typename T>
	inline Plane<T>::Plane()
	{
		Vec<T, 3> e3 ;
		normal_ = e3;
		d_ = 0;
	}

	template<typename T>
	inline Plane<T>::Plane(const Point3<T> p1, const Point3<T> p2, const Point3<T> p3)
	{
		CM::Vec<T, 3> e3 = p2 - p1;
		CM::Vec<T, 3> e1 = p3 - p2;
		normal_ = CM::utils::cross<float>(e3, e1).normalized();
		d_ = p1 * normal_;
	}

	template<typename T>
	void Plane<T>::print()
	{
		std::cout << "normal:" << std::endl;
		normal_.print();
		std::cout << "d=" << d_ << std::endl;
	}

	template<typename T>
	inline Plane<T>::~Plane()
	{
	}

}