// tests.cpp: 定义应用程序的入口点。
//

#include "tests.h"
#include "math_test/vec_test.h"

using namespace std;
int main()
{
	cout << "TEST START" << endl;
	vec_test::vecMultTest();
	cout << "TEST END" << endl;
	return 0;
}
