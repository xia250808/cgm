#pragma once
#include <array>
#include <iostream>



namespace cgm::math {

	template<typename T, size_t N>
	class Mat;

	template <typename T, size_t N>
	class Vec {
		static_assert(N > 0, "Vector dimension must be greater than 0");
		std::array<T, N> data_;
	public:
		Vec() : data_{ T{} } {};
		Vec(std::array<T, N> arr) :data_(arr) {};

		void print()const;

		bool operator==(const Vec<T, N>& other) const noexcept;

		T& operator[](size_t i) {
			if (i > N) throw std::out_of_range("Vec index out of range");
			return data_[i];
		}
		const T& operator[](size_t i) const {
			if (i > N) throw std::out_of_range("Vec index out of range");
			return data_[i];
		}

		T length() const;

		Vec<T, N> normalized() const;

		Vec<T, N> operator+(const Vec<T, N>& other)const;

		Vec<T, N> operator-(const Vec<T, N>& other)const;

		T operator*(const Vec<T, N>& other)const;
		
		template<typename Scalar>
		Vec operator*(Scalar k)const {
			return k * *this;
		}

		Vec operator*(const cgm::math::Mat<T, N> mat)const;

	};

	template<typename Scalar,typename T,size_t N>
	Vec<T, N> operator*(Scalar k, const Vec<T, N>& vec) {
		Vec<T,N> retVec = vec;
		for (size_t i = 0; i < N; ++i)
		{
			retVec[i] *= k;
		}

		return retVec;
	}

	template<typename T, size_t N>
	T Vec<T, N>::operator*(const Vec<T, N>& other)const {

		T sum = T(0);
		for (size_t i = 0; i < N; i++)
		{
			sum += data_[i] * other[i];
		}

		return sum;

	}

	template<typename T, size_t N>
	inline void Vec<T, N>::print() const
	{
		for (size_t i = 0; i < N; ++i) {
			std::cout << data_[i] << "\t";
		}
		std::cout << std::endl;
	}

	template<typename T, size_t N>
	inline bool Vec<T, N>::operator==(const Vec<T, N>& other) const noexcept
	{


		if constexpr (std::is_floating_point_v<T>)
		{
			constexpr T epsilon = std::numeric_limits<T>::epsilon() * N;
			for (size_t i = 0; i < N; ++i)
			{
				if (std::abs(data_[i] - other.data_[i]) > epsilon) return false;
			}
		}
		else
		{
			for (size_t i = 0; i < N; ++i)
			{
				if (data_[i] != other.data_[i]) return false;
			}
		}
		return true;

	}

	template<typename T, size_t N>
	inline T Vec<T, N>::length() const
	{
		T sum = 0;
		for (size_t i = 0; i < N; i++)
		{
			sum += data_[i] * data_[i];
		}
		return sqrt(sum);
	}

	template<typename T, size_t N>
	inline Vec<T, N> Vec<T, N>::normalized() const
	{
		T len = length();
		return len == 0 ? *this : (T(1) / len) * *this;
	};

	template<typename T, size_t N>
	inline Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& other) const
	{
		Vec<T, N> retVec;
		for (size_t i = 0; i < N; ++i)
		{
			retVec[i] = data_[i] + other.data_[i];
		}
		return retVec;
	}

	template<typename T, size_t N>
	inline Vec<T, N> Vec<T, N>::operator-(const Vec<T, N>& other) const
	{
		Vec<T, N> retVec;
		for (size_t i = 0; i < N; ++i)
		{
			retVec[i] = data_[i] - other.data_[i];
		}
		return retVec;
	}

	template<typename T, size_t N>
	inline Vec<T, N> Vec<T, N>::operator*(const Mat<T, N> mat) const
	{
		Vec retVec;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				retVec[i] += data_[j] * mat(i, j);
			}
		}
		return retVec;
	}

}
