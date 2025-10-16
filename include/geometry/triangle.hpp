#pragma once

#include "geometry/geo_core.hpp"

namespace cgm::geometry {

	template<typename T>
	class Triangle
	{
	public:
		Triangle(const std::array<Point3<T>, 3>& vertices);
		Triangle(const Point3<T>& p0, const Point3<T>& p1, const Point3<T>& p2);
		void print();
		T area();
		Vec3<T> normal();
		bool isValid();

	private:
		std::array<Point3<T>, 3> vertices_;
		mutable bool isAreaValid_;
		mutable bool isNormalValid_;
		mutable Vec3<T> cachedNormal_; 
		mutable T cachedArea_;

	};

	template<typename T>
	inline Triangle<T>::Triangle(const std::array<Point3<T>, 3>& vertices)
	{
		vertices_[0] = vertices[0];
		vertices_[1] = vertices[1];
		vertices_[2] = vertices[2];
		isAreaValid_ = false;
		isNormalValid_ = false;
		cachedNormal_ = Vec3<T>();
		cachedArea_ = T(0);
	}

	template<typename T>
	inline Triangle<T>::Triangle(const Point3<T>& p0, const Point3<T>& p1, const Point3<T>& p2)
	{
		vertices_[0] = p0;
		vertices_[1] = p1;
		vertices_[2] = p2;
		isAreaValid_ = false;
		isNormalValid_ = false;
		cachedNormal_ = Vec3<T>();
		cachedArea_ = T(0);
	}

	template<typename T>
	void Triangle<T>::print()
	{
		for (size_t i = 0; i < 3; i++)
		{
			vertices_[i].print();
		}
	}
	template<typename T>
	bool Triangle<T>::isValid() {
		return !CM::is_zero(area());
	}

	template<typename T>
	T Triangle<T>::area() {
		if (isAreaValid_)
		{
			return cachedArea_;
		}
		else
		{
			Vec3<T> vec1 = vertices_[1] - vertices_[0];
			Vec3<T> vec2 = vertices_[2] - vertices_[1];
			cachedArea_ = CM::utils::cross(vec1, vec2).length() / 2;
			isAreaValid_ = true;
			return cachedArea_;
		}		
	}
	template<typename T>
	Vec3<T> Triangle<T>::normal() {
		if (isNormalValid_)
		{
			return cachedNormal_;
		}
		else
		{
			Vec3<T> vec1 = vertices_[1] - vertices_[0];
			Vec3<T> vec2 = vertices_[2] - vertices_[1];
			cachedNormal_ = CM::utils::cross(vec1, vec2).normalized();
			isNormalValid_ = true;
			return cachedNormal_;
		}
	}

}
