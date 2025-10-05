//#include "math/quat.hpp"
//
//namespace cgm::math {
//	template<typename T>
//	Mat<T, 3> transToMat3() {
//		Mat<T, 3> retMat3;
//		retMat3(0, 0) = 1 - 2 * y_ * y_ - 2 * z_ * z_;
//		retMat3(0, 1) = 2 * x_ * y_ + 2 * w_ * z_;
//		retMat3(0, 2) = 2 * x_ * z_ - 2 * w_ * y_;
//
//		retMat3(1, 0) = 2 * x_ * y_ - 2 * w_ * z_;
//		retMat3(1, 1) = 1 - 2 * x_ * x_ - 2 * z_ * z_;
//		retMat3(1, 2) = 2 * y_ * z + 2 * w_ * x_;
//
//		retMat3(2, 0) = 2 * x_ * z_ + 2 * w_ * y_;
//		retMat3(2, 1) = 2 * y_ * z_ - 2 * w_ * x_;
//		retMat3(2, 1) = 1 - 2 * x_ * x_ - 2 * y_ * y_;
//
//		return retMat3;
//
//	}
//}

