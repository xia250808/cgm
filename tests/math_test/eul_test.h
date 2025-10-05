#pragma
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "utill/utill.h"
#include "math/​math.hpp"

class eul_test
{
public:
	eul_test() {
		/*eul_print_test();
		eul_mat3_test();
		eul_quat_test();
		mat_quat_test();*/
		quat_eul_test();
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
		std::string result = (Mat3A == Mat3B) ? "transToMat3 work!" : "transToMat3 not work!";
		cout << result << endl;

	}

	static void eul_quat_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Quat<float> quatA = eulA.transToQuat();
		Mat<float, 3> Mat3A = quatA.transToMat3();
		Mat<float, 3> Mat3B = eulA.transToMat3();
		std::string result = (Mat3A == Mat3B) ? "EultransToQuat work! \t QuattransToMat3 work!" : "EultransToQuat not work! \t QuattransToMat3 not work!";
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
		Eul<float> eulB = quatA.transToEulYxz();
		std::string result = (eulA == eulB) ? "QuatTransToEul work! " : "QuatTransToEul not work! ";
		cout << result << endl;
	}

private:

};