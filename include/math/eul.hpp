#pragma once
#include <numbers> 

namespace cgm::math {

	template<typename T, size_t N>
	class Mat;


	enum class RotationOrder { XYZ, YZX, ZXY, XZY, YXZ, ZYX };
	

	template<typename T>
	class Eul {
	private:
		T epsilon_; // 角度归一化的误差容限（类型与T一致）
		Mat<T, 3> rx(T theta) const{
			return Mat<T, 3>({ {
				{1, 0, 0},
				{0, cos(theta), sin(theta)},
				{0, -sin(theta), cos(theta)}
			} });
		}

		Mat<T, 3> ry(T theta) const {
			return Mat<T, 3>({ {
				{cos(theta), 0, -sin(theta)},
				{0, 1, 0},
				{sin(theta), 0, cos(theta)}
			} });
		}

		Mat<T, 3> rz(T theta) const{
			return Mat<T, 3>({ {
				{cos(theta), sin(theta), 0},
				{ -sin(theta), cos(theta), 0 },
				{ 0, 0, 1 }
			} });
		}

	public:
		T  t1_;
		T  t2_;
		T  t3_;
		RotationOrder ro_ = RotationOrder::YXZ;

		Eul(T theta1 = T(0), T theta2 = T(0), T theta3 = T(0), RotationOrder order = RotationOrder::YXZ) : t1_(theta1), t2_(theta2), t3_(theta3),ro_(order) {};
		// XYZ, YZX, ZXY, XZY, YXZ, ZYX 
		bool operator==(const Eul& other)const {
			constexpr T epsilon = std::numeric_limits<T>::epsilon() * 3;
			if (ro_!= other.ro_)return false;
			if (std::abs(t1_ - other.t1_) > epsilon || std::abs(t2_ - other.t2_) > epsilon || std::abs(t3_ - other.t3_) > epsilon) {
				return false;
			}
			return true;
		}

		Mat<T, 3> transToMat3() const{
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

			};

		};
		T normalize_angle(T angle) const {
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

		void ptint() const {
			T theta1 = normalize_angle(t1_);
			T theta2 = normalize_angle(t2_);
			T theta3 = normalize_angle(t3_);

			switch (ro_) {
			case RotationOrder::XYZ:
				std::cout << "Rotation Order : XYZ \t"<< theta1 << "\t" << theta2 << "\t" << theta3 << "\t";
				break;
			case RotationOrder::YZX:
				std::cout << "Rotation Order : YZX \t" << theta1 << "\t"  << theta2 << "\t" << theta3 << "\t";
				break;
			case RotationOrder::ZXY:
				std::cout << "Rotation Order : ZXY \t" << theta1 << "\t"  << theta2 << "\t" << theta3 << "\t";
				break;
			case RotationOrder::XZY:
				std::cout << "Rotation Order : XZY \t" << theta1 << "\t"  << theta2 << "\t" << theta3 << "\t";
				break;
			case RotationOrder::YXZ:
				std::cout << "Rotation Order : YXZ \t" << theta1 << "\t"  << theta2 << "\t" << theta3 << "\t";
				break;
			case RotationOrder::ZYX:
				std::cout << "Rotation Order : ZYX \t" << theta1 << "\t"  << theta2 << "\t" << theta3 << "\t";

			};
			std::cout << std::endl;

		};

		
	};
}