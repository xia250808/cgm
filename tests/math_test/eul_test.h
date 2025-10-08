#pragma
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "utill/utill.h"
#include "math/​math.hpp"
#include "rotation/eul.hpp"

using namespace cgm::rotation;
//using namespace cgm::math;

class eul_test
{
public:
	eul_test() {
		eul_print_test();
		eul_mat3_test();
		eul_quat_test();
		mat_quat_test();
		quat_eul_test();
		mat_eul_test();
	}

	static void eul_print_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		eulA.ptint();
	}
	static void eul_mat3_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Mat<float, 3> Mat3A = eulA.transToMat3();
		glm::mat4 rotationMatrix = glm::eulerAngleYXZ(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Mat<float,3> Mat3B = Utill::transGlmMat4ToMat3(rotationMatrix);
		std::string result = (Mat3A == Mat3B) ? "EulTransToMat3 work!" : "EulTransToMat3 not work!";
		cout << result << endl;

	}

	static void eul_quat_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Quat<float> quatA = eulA.transToQuat();
		Mat<float, 3> Mat3A = quatA.transToMat3();
		Mat<float, 3> Mat3B = eulA.transToMat3();
		std::string result = (Mat3A == Mat3B) ? "EulTransToQuat work!" : "EulTransQuat not work!";
		cout << result << endl;
	}

	static void mat_quat_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Quat<float> quatA = eulA.transToQuat();
		Quat<float> quatB = eulA.transToMat3().transToQuat();
		std::string result = (quatA == quatB) ? "MatTransToQuat work! " : "MatTransToQuat not work! ";
		cout << result << endl;
	}

	static void quat_eul_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Quat<float> quatA = eulA.transToQuat();
		Eul<float> eulB = Eul<float>::createFromQuat(quatA);
		std::string result = (eulA == eulB) ? "QuatTransToEul work! " : "QuatTransToEul not work! ";
		cout << result << endl;
	}

	static void mat_eul_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Quat<float> quatA = eulA.transToQuat();
		Mat<float, 3> Mat3A = eulA.transToMat3();
		Eul<float> eulC = Eul<float>::createFromQuat(quatA);
		Eul<float> eulD = Eul<float>::createFromMat3(Mat3A);
		std::string result = (eulC == eulD) ? "createFromQuat work!  createFromMat3 work!" : "createFromQuat not work! createFromQuat not work! ";
		cout << result << endl;
	}

private:

};