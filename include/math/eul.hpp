#pragma once
#include <numbers> 

namespace cgm::math {

	
	template<typename T, size_t N>
	class Mat;

	template<typename T>
	class Quat;

	enum class RotationOrder { XYZ, YZX, ZXY, XZY, YXZ, ZYX };

	template<typename T>
	class Eul {
	private:
		T epsilon_ = std::numeric_limits<T>::epsilon() * 3; // 角度归一化的误差容限（类型与T一致）

		Mat<T, 3> rx(T theta) const;

		Mat<T, 3> ry(T theta) const;

		Mat<T, 3> rz(T theta) const;

	public:
		T  t1_;
		T  t2_;
		T  t3_;
		RotationOrder ro_ = RotationOrder::YXZ;

		Eul(std::array<T, 3> arr) : t1_(arr[0]), t2_(arr[1]), t3_(arr[2]) {};

		Eul(T theta1 = T(0), T theta2 = T(0), T theta3 = T(0), RotationOrder order_ = RotationOrder::YXZ) : t1_(theta1), t2_(theta2), t3_(theta3),ro_(order_) {};

		bool operator==(const Eul& other)const;

		Mat<T, 3> transToMat3() const;

		Quat<T> transToQuat()const;

		T normalize_angle(T angle) const;

		void ptint() const;
	
	};

	template<typename T>
	Mat<T, 3> Eul<T>::rx(T theta) const {
		return Mat<T, 3>({ {
			{1, 0, 0},
			{0, cos(theta), sin(theta)},
			{0, -sin(theta), cos(theta)}
		} });
	}

	template<typename T>
	Mat<T, 3> Eul<T>::ry(T theta) const {
		return Mat<T, 3>({ {
			{cos(theta), 0, -sin(theta)},
			{0, 1, 0},
			{sin(theta), 0, cos(theta)}
		} });
	}

	template<typename T>
	Mat<T, 3> Eul<T>::rz(T theta) const {
		return Mat<T, 3>({ {
			{cos(theta), sin(theta), 0},
			{ -sin(theta), cos(theta), 0 },
			{ 0, 0, 1 }
		} });
	}

	template<typename T>
	bool Eul<T>::operator==(const Eul& other)const {
		if (ro_ != other.ro_)return false;
		if (std::abs(t1_ - other.t1_) > epsilon_)return false;
		if (std::abs(t2_ - other.t2_) > epsilon_)return false;
		if (std::abs(t3_ - other.t3_) > epsilon_)return false;
		return true;
	}

	template<typename T>
	T Eul<T>::normalize_angle(T angle) const {
		using std::fmod;       // 允许ADL查找fmod（支持自定义类型）
		constexpr T pi = std::numbers::template pi_v<T>;

		// 1. 将角度映射到 [-π, π) 区间
		angle = fmod(angle + pi, 2 * pi) - pi;

		// 2. 处理边界情况（避免浮点误差）
		if (angle > pi - epsilon_) {
			angle -= 2 * pi;
		}
		if (angle < -pi + epsilon_) {
			angle += 2 * pi;
		}

		return angle;
	}

	template<typename T>
	Mat<T, 3> Eul<T>::transToMat3() const {
		switch (ro_) {
		case RotationOrder::XYZ:
			return rz(t3_) * ry(t2_) * rx(t1_);
		case RotationOrder::YZX:
			return rx(t3_) * rz(t2_) * ry(t1_);
		case RotationOrder::ZXY:
			return ry(t3_) * rx(t2_) * rz(t1_);
		case RotationOrder::XZY:
			return ry(t3_) * rz(t2_) * rx(t1_);
		case RotationOrder::YXZ:
			return rz(t3_) * rx(t2_) * ry(t1_);
		case RotationOrder::ZYX:
			return rx(t3_) * ry(t2_) * rz(t1_);
		default:
			return rz(t3_) * rx(t2_) * ry(t1_);
		};

	};

	template<typename T>
	Quat<T> Eul<T>::transToQuat()const {

		T y = normalize_angle(t1_);
		T p = normalize_angle(t2_);
		T r = normalize_angle(t3_);
		T cy2 = cos(y / 2), sy2 = sin(y / 2);
		T cp2 = cos(p / 2), sp2 = sin(p / 2);
		T cr2 = cos(r / 2), sr2 = sin(r / 2);

		Quat<T> retQuat;

		retQuat.w_ = cy2 * cp2 * cr2 + sy2 * sp2 * sr2;
		retQuat.x_ = cy2 * sp2 * cr2 + sy2 * cp2 * sr2;
		retQuat.y_ = sy2 * cp2 * cr2 - cy2 * sp2 * sr2;
		retQuat.z_ = cy2 * cp2 * sr2 - sy2 * sp2 * cr2;

		return retQuat;
	}

	template<typename T>
	void Eul<T>::ptint() const {
		T theta1 = normalize_angle(t1_);
		T theta2 = normalize_angle(t2_);
		T theta3 = normalize_angle(t3_);

		switch (ro_) {

		case RotationOrder::XYZ:
			std::cout << "Rotation Order : XYZ \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
			break;
		case RotationOrder::YZX:
			std::cout << "Rotation Order : YZX \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
			break;
		case RotationOrder::ZXY:
			std::cout << "Rotation Order : ZXY \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
			break;
		case RotationOrder::XZY:
			std::cout << "Rotation Order : XZY \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
			break;
		case RotationOrder::YXZ:
			std::cout << "Rotation Order : YXZ \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
			break;
		case RotationOrder::ZYX:
			std::cout << "Rotation Order : ZYX \t" << theta1 << "\t" << theta2 << "\t" << theta3 << "\t";

		};
		std::cout << std::endl;

	};


}