#pragma once
#include "geometry/geometry.hpp"

using namespace cgm::geometry;
class plane_test
{
public:
	static void print_test() {
		Plane<float> planeA;
		planeA.print();
	}

	static void create_plane_test() {
		std::array<float, 3> arr1A = { 1.1f,2.2f,3.3f };
		Point3<float> pointA = Point3<float>(arr1A);
		std::array<float, 3> arr1B = { -1.1f,4.2f,2.3f };
		Point3<float> pointB = Point3<float>(arr1B);
		std::array<float, 3> arr1C = { -1.1f,5.2f,5.3f };
		Point3<float> pointC = Point3<float>(arr1C);
		Plane<float> planeA = Plane<float>(pointA, pointB, pointC);
		planeA.print();
	}

	plane_test();
	~plane_test();

private:

};

plane_test::plane_test()
{
	//print_test();
	create_plane_test();
}

plane_test::~plane_test()
{
}