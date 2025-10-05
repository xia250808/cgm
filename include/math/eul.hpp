#pragma once

namespace cgm::math {

	template<typename T, size_t N>
	class Mat;


	enum class RotationOrder { XYZ, YZX, ZXY, XZY, YXZ, ZYX };
	

	template<typename T>
	class Eul {
	private:
		Mat<T, 3> rx(T theta) {
			return Mat<T, 3>({ {
				{1, 0, 0},
				{0, cos(theta), sin(theta)},
				{0, -sin(theta), cos(theta)}
			} });
		}

		Mat<T, 3> ry(T theta) {
			return Mat<T, 3>({ {
				{cos(theta), 0, -sin(theta)},
				{0, 1, 0},
				{sin(theta), 0, cos(theta)}
			} });
		}

		Mat<T, 3> rz(T theta) {
			return Mat<T, 3>({ {
				{cos(theta), sin(theta), 0},
				{ -sin(theta), cos(theta), 0 },
				{ 0, 0, 1 }
			} });
		}

	public:
		T  t1;
		T  t2;
		T  t3;
		RotationOrder ro = RotationOrder::YXZ;
		void print() {
			std::cout << "hello eul" << std::endl;
		}

		Eul(T theta1 = T(0), T theta2 = T(0), T theta3 = T(0), RotationOrder order = RotationOrder::YXZ) : t1(theta1), t2(theta2), t3(theta3),ro(order) {};
		//T normalize_angle(T angle);
		// XYZ, YZX, ZXY, XZY, YXZ, ZYX 
		Mat<T, 3> transToMat3() {
			switch (ro) {
			case RotationOrder::XYZ:
				return rz(t3) * ry(t2) * rx(t1);
			case RotationOrder::YZX:
				return rx(t3) * rz(t2) * ry(t1);
			case RotationOrder::ZXY:
				return ry(t3) * rx(t2) * rz(t1);
			case RotationOrder::XZY:
				return ry(t3) * rz(t2) * rx(t1);
			case RotationOrder::YXZ:
				return rz(t3) * rx(t2) * ry(t1);
			case RotationOrder::ZYX:
				return rx(t3) * ry(t2) * rz(t1);

			};

		};

		
	};
}