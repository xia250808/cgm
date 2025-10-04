#pragma once

namespace cgm::math {
	template<typename T,size_t N>
	class Mat {
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

	};
}