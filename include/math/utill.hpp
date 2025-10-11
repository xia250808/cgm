#pragma once
namespace cgm::math {
	template<typename T, size_t N>
	class Vec;

	template<typename T>
	class Utills
	{
	public:
		static Vec<T, 3> cross(const Vec<T, 3>& a, const Vec<T, 3>& b);



	private:



	};

	template<typename T>
	inline Vec<T, 3> Utills<T>::cross(const Vec<T, 3>& a, const Vec<T, 3>& b)
	{
		return Vec<T, 3>();
	}

}