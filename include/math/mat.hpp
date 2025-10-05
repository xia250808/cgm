#pragma once
#include <numbers> 

namespace cgm::math {

	template<typename T>
	class Eul;

	template<typename T,size_t N>
	class Mat {
		static_assert(N > 0, "Matrix order must be at least 1");

	private:

		Mat<T, N - 1> createMinor(size_t excludeRow, size_t excludeCol) const{
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

		T cofactor(size_t i, size_t j) const {
			static_assert(N >= 1, "Cofactor requires matrix order >= 1");
			int sig = (i + j) % 2 == 0 ? 1 : -1;
			Mat<T, N - 1> minor = createMinor(i, j);
			return sig * (minor.determinant());
		}
		Mat adj() const {
			Mat retMat;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++) {
					retMat(j, i) = cofactor(i, j);
				}
			}
			return retMat;

		}

	public:
		using Row = std::array<T, N>;
		using Data = std::array<Row, N>;
		Data data_;
		Mat() :data_{} {};
		Mat(Data arr2) : data_(arr2) {};
		Mat(std::array<T,N*N> arr1) {
			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < N; ++j)
				{
					data_[i][j] = arr1[i * j + j];
				}
			}
		};
		static Mat<T, N> identity() {
			Mat<T, N> retMat;
			for (size_t i = 0; i < N; i++)
			{
				retMat(i, i) = T(1);
			}
			return retMat;
		}
		void print() {
			for (size_t i = 0; i < N; ++i) {
				for (size_t j = 0; j < N; ++j) {
					std::cout << data_[i][j] << "\t";
				}
				std::cout << std::endl;
			}
		}

		T& operator()(size_t row,size_t colum) {
			if (row >= N || colum >= N) {
				throw std::out_of_range("Matrix indices out of range");
			}
			return data_[row][colum];
		}

		const T& operator()(size_t row, size_t colum)const {
			if (row >= N || colum >= N) {
				throw std::out_of_range("Matrix indices out of range");
			}
			return data_[row][colum];
		}

		

		Mat transpose() const {
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

		Mat operator*(const Mat& other) const {
			Mat retMat;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0;  j < N;  j++)
				{
					for (size_t k = 0; k < N; k++)
					{
						retMat(i, j) += data_[i][k] * other(k, j);
					}

				}
			}
			return retMat;
		}

		Mat operator*(const T scalar)const {
			Mat retMat;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++) {
					retMat(i, j) = data_[i][j] * scalar;
				}
			}
			return retMat;
		}
		friend Mat operator*(const T scalar, const Mat& mat) {
			return mat * scalar;
		}

		bool operator==(const Mat& other)const {
			if constexpr (std::is_floating_point_v<T>)
			{
				constexpr T epsilon = std::numeric_limits<T>::epsilon() * N;
				for (size_t i = 0; i < N; ++i)
				{
					for (size_t j = 0; j < N; j++)
					{
						if (std::abs(data_[i][j] - other(i, j)) > epsilon) return false;
					}					
				}
			}
			else
			{
				for (size_t i = 0; i < N; ++i)
				{
					for (size_t j = 0; j < N; j++)
					{
						if (data_[i][j] != other(i, j)) return false;
					}
				}
			}
			return true;
		}
		const Row& row(size_t i)const {
			if (i >= N) {
				throw std::out_of_range("Matrix indices out of range");
			}
			return data_[i];
		};

		Row col(size_t j) {
			if (j >= N) {
				throw std::out_of_range("Matrix indices out of range");
			}
			Row colum;
			for (size_t i = 0; i < N; i++)
			{
				colum[i] = data_[i][j];
			}
			return colum;
		};


		T determinant() {
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

		Mat inverse() {
			return (T(1) / determinant()) * adj();
		}

		Eul<T> transToEulYxz()const {
			T p;
			T y;
			T r;
			constexpr T pi = std::numbers::template pi_v<T>;

			T sp = -data_[2][1];
			
			if (sp <= -1.0f) {

				p = -pi / 2;
			}
			else if (sp >= 1.0f) {

				p = pi / 2;

			}
			else {

				p = asin(sp);
			}
			if (fabs(sp) > 0.9999f)
			{
				r = 0.0f;
				y = atan2(data_[0][2], data_[0][0]);
			}
			else {
				y = atan2(data_[2][0], data_[2][2]);
				r = atan2(data_[0][1], data_[1][1]);
			}
			return Eul<T>(y, p, r);
		}
	};
}