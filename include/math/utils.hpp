#pragma once
namespace cgm::math::utils {

	template<typename T>
	Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b)
	{
		T retX = a[1] * b[2] - a[2] * b[1];
		T retY = a[2] * b[0] - a[0] * b[2];
		T retZ = a[0] * b[1] - a[1] * b[0];
		return Vec3<T>({retX,retY,retZ});
	}
}