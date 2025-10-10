#pragma once
#include <numbers> 

namespace cgm::math {

	template<typename T>
	class Quat;

	template<typename T, size_t N>
	class Vec;

	template<typename T,size_t N>
	class Mat {
		static_assert(N > 0, "Matrix order must be at least 1");

	private:

		Mat<T, N - 1> createMinor(size_t excludeRow, size_t excludeCol) const;

		T cofactor(size_t i, size_t j) const;

		Mat adj() const;

	public:
		using Row = Vec<T, N>;
		using Data = std::array<Row, N>;
		Data data_;

		Mat() :data_{} {};
		Mat(Data arr2) : data_(arr2) {};
		Mat(std::array<T,N*N> arr1);
		
		T& operator()(size_t row,size_t colum) {
			if (row >= N || colum >= N) throw std::out_of_range("Matrix indices out of range");
			return data_[row][colum];
		}

		const T& operator()(size_t row, size_t colum)const {
			if (row >= N || colum >= N) throw std::out_of_range("Matrix indices out of range");
			return data_[row][colum];
		}

		static Mat<T, N> identity();

		void print();

		Mat transpose() const;

		Mat operator+(const Mat& other) const;

		Mat operator*(const Mat& other) const;

		Mat operator*(const T scalar)const;
		friend Mat operator*(const T scalar, const Mat& mat) {
			return mat * scalar;
		}

		bool operator==(const Mat& other)const;


		const Row& row(size_t i)const {
			if (i >= N) throw std::out_of_range("Matrix indices out of range");
			return data_[i];
		};

		Row colum(size_t j) const {
			if (j >= N) throw std::out_of_range("Matrix indices out of range");
			Row colum;
			for (size_t i = 0; i < N; i++)
			{
				colum[i] = data_[i][j];
			}
			return colum;
		};
		T determinant()const;

		Mat inverse() {
			return (T(1) / determinant()) * adj();
		}

		Quat<T> transToQuat()const;


	};


	template<typename T, size_t N>
	inline Mat<T, N - 1> Mat<T, N>::createMinor(size_t excludeRow, size_t excludeCol) const
	{
		if (excludeRow >= N || excludeCol >= N) {
			throw std::out_of_range("Matrix indices out of range");
		}
		Mat<T, N - 1> retMat;
		size_t retMatRowIndex = 0;
		for (size_t i = 0; i < N; i++)
		{
			if (i == excludeRow) continue;
			size_t retMatColIndex = 0;
			for (size_t j = 0; j < N; j++)
			{
				if (j == excludeCol) continue;
				retMat(retMatRowIndex, retMatColIndex) = data_[i][j];
				retMatColIndex++;
			}
			retMatRowIndex++;
		}

		return retMat;
	}

	template<typename T, size_t N>
	inline T Mat<T, N>::cofactor(size_t i, size_t j) const {
		static_assert(N >= 1, "Cofactor requires matrix order >= 1");
		int sig = (i + j) % 2 == 0 ? 1 : -1;
		Mat<T, N - 1> minor = createMinor(i, j);
		return sig * (minor.determinant());
	}

	template<typename T, size_t N>
	inline Mat<T, N> Mat<T, N>::adj() const
	{
		Mat retMat;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++) {
				retMat(j, i) = cofactor(i, j);
			}
		}
		return retMat;

	}

	template<typename T, size_t N>
	inline Mat<T, N>::Mat(std::array<T, N* N> arr1)
	{
		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				data_[i][j] = arr1[i * j + j];
			}
		}
	}

	template<typename T, size_t N>
	inline Mat<T, N> Mat<T, N>::identity()
	{
		Mat<T, N> retMat;
		for (size_t i = 0; i < N; i++)
		{
			retMat(i, i) = T(1);
		}
		return retMat;
	}

	template<typename T, size_t N>
	inline void Mat<T, N>::print()
	{
		for (size_t i = 0; i < N; ++i) {
			data_[i].print();
		}
	}

	template<typename T, size_t N>
	inline Mat<T, N> Mat<T, N>::transpose() const
	{
		Mat retMat;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				retMat(i, j) = data_[j][i];
			}

		}
		return retMat;
	}

	template<typename T, size_t N>
	inline Mat<T, N> Mat<T, N>::operator+(const Mat<T, N>& other) const
	{
		Mat<T, N> retMat;
		for (size_t i = 0; i < N; i++)
		{
			retMat.data_[i] = data_[i] + other.data_[i];
		}
		return retMat;
	}

	template<typename T, size_t N>
	inline Mat<T, N> Mat<T, N>::operator*(const Mat<T, N>& other) const
	{
		Mat<T, N> retMat;

		for (size_t j = 0; j < N; j++)
		{
			Vec<T, N> col = other.colum(j);
			for (size_t i = 0; i < N; i++)
			{
				retMat(i, j) = data_[i] * col;
			}

		}
		return retMat;
	}

	template<typename T, size_t N>
	Mat<T, N> Mat<T, N>::operator*(const T scalar)const {
		Mat retMat;
		for (size_t i = 0; i < N; i++)
		{
			retMat.data_[i] = data_[i] * scalar;
		}
		return retMat;
	}

	template<typename T, size_t N>
	bool Mat<T, N>::operator==(const Mat& other)const {
		for (size_t i = 0; i < N; ++i)
		{
			if (data_[i] != data_[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T, size_t N>
	inline T Mat<T, N>::determinant()const {
		if constexpr (N == 0) {
			return T(1); // 空矩阵行列式为 1
		}
		else if constexpr (N == 1) {
			return data_[0][0];
		}
		else if constexpr (N == 2) {
			return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
		}
		else {
			T det = T(0);
			for (size_t j = 0; j < N; j++)
			{
				det += data_[0][j] * cofactor(0, j);
			}
			return det;
		}
	}

	template<typename T, size_t N>
	inline Quat<T> Mat<T, N>::transToQuat() const
	{
		static_assert(N >= 3, "Matrix must be at least 3x3 to extract Euler angles");
		T w, x, y, z;
		T _w, _x, _y, _z;
		_w = data_[0][0] + data_[1][1] + data_[2][2];
		_x = data_[0][0] - data_[1][1] - data_[2][2];
		_y = -data_[0][0] + data_[1][1] - data_[2][2];
		_z = -data_[0][0] - data_[1][1] + data_[2][2];

		T  maxNum = _w;
		size_t maxNumIndex = 0;
		if (_x > maxNum)
		{
			maxNum = _x;
			maxNumIndex = 1;
		}
		if (_y > maxNum)
		{
			maxNum = _y;
			maxNumIndex = 2;
		}
		if (_z > maxNum)
		{
			maxNum = _z;
			maxNumIndex = 3;
		}

		T biggestVal = sqrt(maxNum + 1) * 0.5f;
		T mult = 0.25f / biggestVal;

		switch (maxNumIndex) {
		case 0:
			w = biggestVal;
			x = (data_[1][2] - data_[2][1]) * mult;
			y = (data_[2][0] - data_[0][2]) * mult;
			z = (data_[0][1] - data_[1][0]) * mult;
			break;
		case 1:
			x = biggestVal;
			w = (data_[1][2] - data_[2][1]) * mult;
			y = (data_[0][1] - data_[1][0]) * mult;
			z = (data_[2][0] - data_[0][2]) * mult;
			break;
		case 2:
			y = biggestVal;
			w = (data_[2][0] - data_[0][2]) * mult;
			x = (data_[0][1] - data_[1][0]) * mult;
			z = (data_[1][2] - data_[2][1]) * mult;
			break;
		case 3:
			z = biggestVal;
			w = (data_[0][1] - data_[1][0]) * mult;
			x = (data_[2][0] - data_[0][2]) * mult;
			y = (data_[1][2] - data_[2][1]) * mult;
			break;
		}

		std::array<T, 4> arr1 = { w,x,y,z };
		return Quat<T>(arr1);
	}
}