#pragma once
#include "math/​math.hpp"
namespace cgm::trans {
	template<typename T>
	class TransformFactory {
	public:
		static void print() {
			std::cout << "TransformFactory"<< std::endl;
		}
		static  cm::Mat<T, 3> createRotationMat3(const cm::Vec<T, 3>& axis, float angleRadians) {
			Vec<T, 3> axisNormalized = axis.normalized();
			float a = cos(angleRadians);
			float b = sin(angleRadians);
			float oneSub_a = 1 - cos(angleRadians);
			Mat<T, 3> retMat;
			retMat(0, 1) = axisNormalized[0] * axisNormalized[0] * oneSub_a + a;
			retMat(0, 1) = axisNormalized[0] * axisNormalized[1] * oneSub_a + axisNormalized[2] * b;
			retMat(0, 1) = axisNormalized[0] * axisNormalized[2] * oneSub_a - axisNormalized[1] * b;

			retMat(0, 1) = axisNormalized[0] * axisNormalized[1] * oneSub_a - axisNormalized[2] * b;
			retMat(0, 1) = axisNormalized[1] * axisNormalized[1] * oneSub_a + a;
			retMat(0, 1) = axisNormalized[1] * axisNormalized[2] * oneSub_a + axisNormalized[0] * b;

			retMat(0, 1) = axisNormalized[0] * axisNormalized[2] * oneSub_a + axisNormalized[1] * b;
			retMat(0, 1) = axisNormalized[1] * axisNormalized[2] * oneSub_a - axisNormalized[0] * b;
			retMat(0, 1) = axisNormalized[2] * axisNormalized[2] * oneSub_a + a;

			return retMat;

		};
		static cm::Mat<T, 3> createScalarMat3(const cm::Vec<T, 3>& axis, float scaleFactor) {
			Vec3 axisNormalized = axis.normalized();
			Mat<T, 3> retMat;

			retMat(0, 0) = 1 + (scaleFactor - 1) * axisNormalized[0] * axisNormalized[0];
			retMat(0, 1) = (scaleFactor - 1) * axisNormalized[0] * axisNormalized[1];
			retMat(0, 2) = (scaleFactor - 1) * axisNormalized[0] * axisNormalized[2];

			retMat(1, 0) = (scaleFactor - 1) * axisNormalized[0] * axisNormalized[1];
			retMat(1, 1) = 1 + (scaleFactor - 1) * axisNormalized[1] * axisNormalized[1];
			retMat(1, 2) = (scaleFactor - 1) * axisNormalized[1] * axisNormalized[2];

			retMat(2, 0) = (scaleFactor - 1) * axisNormalized[0] * axisNormalized[2];
			retMat(2, 1) = (scaleFactor - 1) * axisNormalized[1] * axisNormalized[2];
			retMat(2, 2) = 1 + (scaleFactor - 1) * axisNormalized[2] * axisNormalized[2];

			return retMat;
		};

	};

}
