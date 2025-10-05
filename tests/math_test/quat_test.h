#pragma

#include "math/​math.hpp"

class quat_test
{
public:
	quat_test() {
		quat_print_test();
	}

	static void quat_print_test() {
		Quat<float> quatA;
		std::array<float, 4> arr1 = { 1,2,3,4 };
		Quat<float> quatB = Quat<float>(arr1);
		quatB.print();
		quatA.print();

	}

private:

};