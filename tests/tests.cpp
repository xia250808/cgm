// tests.cpp: 定义应用程序的入口点。
//

#include "tests.h"
#include "math_test/vec_test.h"
#include "math_test/mat_test.h"

using namespace std;
int main()
{
	cout << "TEST START" << endl;
	vec_test::vecMultTest();
	vec_test::vecMultMatTest();
	//mat_test::print_func_test();
	mat_test::transpose_test();
	mat_test::mult_equal_test();
	mat_test::determinant_test();
	mat_test::inverse_test();
	cout << "TEST END" << endl;
	return 0;
}
