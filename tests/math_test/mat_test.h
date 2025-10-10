
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
		std::array<Vec<float, 4>, 4> VecArr = { {
			{{ 1.0f,5.0f,4.0f,2.0f }},
			{{ 7.0f,4.0f,7.1f,2.0f }},
			{{ 3.0f,5.0f,-1.0f,2.0f }},
			{{ 8.0f,6.0f,5.0f,9.0f }}
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(VecArr);
		if (mat4.transpose().transpose() == mat4)
		{
			std::cout << "transpose method  work!" << std::endl;
		};
	}

	static void mult_equal_test() {
		std::array<Vec<float, 4>, 4> VecArr = { {
			{{ 1.0f,5.0f,4.0f,2.0f }},
			{{ 7.0f,4.0f,7.1f,2.0f }},
			{{ 3.0f,5.0f,-1.0f,2.0f }},
			{{ 8.0f,6.0f,5.0f,9.0f }}
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(VecArr);
		if (5.0f*mat4 == mat4*5.0f)
		{
			std::cout << "mult and reload operator ==  work!" << std::endl;
		}
	}


	static void determinant_test() {
		std::array<Vec<float, 4>, 4> VecArr = { {
			{{ 1.0f,5.0f,4.0f,2.0f }},
			{{ 7.0f,4.0f,7.1f,2.0f }},
			{{ 3.0f,5.0f,-1.0f,2.0f }},
			{{ 8.0f,6.0f,5.0f,9.0f }}
		} };
		Mat<float, 4> mat4 = Mat<float, 4>(VecArr);
		float det = mat4.determinant();
		std::cout << det << std::endl;
	}

	static void inverse_test() {
		std::array<Vec<float, 4>, 4> VecArr = { {
			{{ 1.0f,5.0f,4.0f,2.0f }},
			{{ 7.0f,4.0f,7.1f,2.0f }},
			{{ 3.0f,5.0f,-1.0f,2.0f }},
			{{ 8.0f,6.0f,5.0f,9.0f }}
		} };
		std::array<float, 4> arr1 = { 1,2,3,4 };
		Vec<float, 4> VecA = Vec(arr1);
		Mat<float, 4> mat4 = Mat<float, 4>(VecArr);
		if (VecA*mat4*mat4.inverse() == VecA)
		{
			std::cout << "inverse method work!"<<std::endl;
		}
	}

	mat_test() {
		print_func_test();
		transpose_test();
		mult_equal_test();
		determinant_test();
		inverse_test();
	}
	
};