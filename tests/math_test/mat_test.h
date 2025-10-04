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
			std::cout << "transpose func  work!" << std::endl;
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
};