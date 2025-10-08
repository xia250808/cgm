#pragma once
#include <iostream>

namespace cgm::math {
	template<typename T, size_t N>
	class Mat;


	template<typename T>
	class Quat{
	private:
		T epsilon_ = std::numeric_limits<T>::epsilon() * 4;
		// 模长平方
		T normSquared() const {
			return w_ * w_ + x_ * x_ + y_ * y_ + z_ * z_;
		}

		// 模长
		T norm() const {
			return std::sqrt(normSquared());
		}
	public:
		T w_;
		T x_;
		T y_;
		T z_;

		Quat() : w_(1), x_(0), y_(0), z_(0) {};
		Quat(T w,T x,T y,T z):w_(w), x_(x), y_(y), z_(z){}
		Quat(std::array<T, 4> arr) : w_(arr[0]), x_(arr[1]), y_(arr[2]), z_(arr[3]) {}
		void print() {
			std::cout << "Quat : " << "\t";
			std::cout << "w_ = " << w_<< "\t";
			std::cout << "x_ = " << x_ << "\t";
			std::cout << "y_ = " << y_ << "\t";
			std::cout << "z_ = " << z_ << "\t";
			std::cout << std::endl;
		}
		
		// 共轭
		Quat conjugate() const {
			return Quat(w_, -x_, -y_, -z_);
		}

		
		bool isUnit() {
			constexpr T epsilon = std::numeric_limits<T>::epsilon() * 4;
			return abs(T(1) - norm()) < epsilon;
		}

		Mat<T, 3> transToMat3() const {
			Mat<T, 3> retMat3;
			retMat3(0, 0) = 1 - 2 * y_ * y_ - 2 * z_ * z_;
			retMat3(0, 1) = 2 * x_ * y_ + 2 * w_ * z_;
			retMat3(0, 2) = 2 * x_ * z_ - 2 * w_ * y_;

			retMat3(1, 0) = 2 * x_ * y_ - 2 * w_ * z_;
			retMat3(1, 1) = 1 - 2 * x_ * x_ - 2 * z_ * z_;
			retMat3(1, 2) = 2 * y_ * z_ + 2 * w_ * x_;

			retMat3(2, 0) = 2 * x_ * z_ + 2 * w_ * y_;
			retMat3(2, 1) = 2 * y_ * z_ - 2 * w_ * x_;
			retMat3(2, 2) = 1 - 2 * x_ * x_ - 2 * y_ * y_;

			return retMat3;
		};

		bool operator==(const Quat& other) const {
			if (abs(w_ - other.w_) > epsilon_)return false;
			if (abs(x_ - other.x_) > epsilon_)return false;
			if (abs(y_ - other.y_) > epsilon_)return false;
			if (abs(z_ - other.z_) > epsilon_)return false;
			return true;
		}
		
	};
}