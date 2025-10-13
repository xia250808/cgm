#pragma once
#include "geometry/geometry.hpp"

using namespace cgm::geometry;
class calculate_test
{
	
public:
	calculate_test();
	~calculate_test();

	static void print_test() {
		std::array<float, 3> arr1A = { 1.1f,2.2f,3.3f};
		Point3<float> pointA = Point3<float>(arr1A);
		std::array<float, 3> arr1B = { 2,2,4 };
		Point3<float> pointB = Vec(arr1B);
		LineSegment<float> lineA = LineSegment(pointA, pointB);
		lineA.print();
		std::cout <<lineA.length();
		
	}

private:

};

calculate_test::calculate_test()
{
	print_test();
}

calculate_test::~calculate_test()
{
}