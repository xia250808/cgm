
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "math/​math.hpp"

using cgm::math::Mat;
class mat_test
{
public:
	static void print_func_test() {
		Mat<float, 3> matA = Mat<float, 3>();
		matA.print();
		Mat<float, 4> matI = Mat<float, 4>::identity();
		matI.print();
	}
	static void transpose_test() {
		std::array<std::array<float, 4>, 4> myStdArr = { {
			{ 1.0f,5.0f,4.0f,2.0f },
			{ 7.0f,4.0f,7.1f,2.0f },
			{ 3.0f,5.0f,-1.0f,2.0f },
			{ 8.0f,6.0f,5.0f,9.0f }
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(myStdArr);
		if (mat4.transpose().transpose() == mat4)
		{
			std::cout << "transpose method  work!" << std::endl;
		};
	}

	static void mult_equal_test() {
		std::array<std::array<float, 4>, 4> myStdArr = { {
			{ 1.0f,5.0f,4.0f,2.0f },
			{ 7.0f,4.0f,7.1f,2.0f },
			{ 3.0f,5.0f,-1.0f,2.0f },
			{ 8.0f,6.0f,5.0f,9.0f }
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(myStdArr);
		if (5.0f*mat4 == mat4*5.0f)
		{
			std::cout << "mult and reload operator ==  work!" << std::endl;
		}
	}


	static void determinant_test() {
		std::array<std::array<float, 4>, 4> myArr = { {
			{ 1.0f,5.0f,4.0f,2.0f },
			{ 7.0f,4.0f,7.1f,2.0f },
			{ 3.0f,5.0f,-1.0f,2.0f },
			{ 8.0f,6.0f,5.0f,9.0f }
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(myArr);
		float det = mat4.determinant();
		std::cout << det << std::endl;
	}

	static void inverse_test() {
		std::array<std::array<float, 4>, 4> myArr = { {
			{ 1.0f,5.0f,4.0f,2.0f },
			{ 7.0f,4.0f,7.1f,2.0f },
			{ 3.0f,5.0f,-1.0f,2.0f },
			{ 8.0f,6.0f,5.0f,9.0f }
		} };
		std::array<float, 4> arr1 = { 1,2,3,4 };
		Vec<float, 4> VecA = Vec(arr1);
		Mat<float, 4> mat4 = Mat<float, 4>(myArr);
		if (VecA*mat4*mat4.inverse() == VecA)
		{
			std::cout << "inverse method work!"<<std::endl;
		}
	}
	static void mat3_eul_test() {
		Eul<float> eulA = Eul(glm::radians(65.0f), glm::radians(24.0f), glm::radians(42.0f));
		Mat<float, 3> Mat3A = eulA.transToMat3();
		Eul<float> eulA1 = Mat3A.transToEulYxz();
		std::string result = (eulA == eulA1) ? "transToEulYxz work!" : "transToEulYxz not work!";
		cout << result << endl;

	}

	mat_test() {
		/*print_func_test();
		transpose_test();
		mult_equal_test();
		determinant_test();*/
		mat3_eul_test();
		inverse_test();
	}
	
};