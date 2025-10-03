// tests.cpp: 定义应用程序的入口点。
//

#include "tests.h"
#include "math/vec.hpp"

using namespace std;
using namespace cgm::math;
int main()
{
	cout << "Hello CMake." << endl;
	Vec<float, 4>  vecA;
	std::array<float, 4> arr1 = { 1,2,3,4 };
	Vec<float, 4> VecB = Vec(arr1);
	(VecB +  2*VecB).print();
	return 0;
}
