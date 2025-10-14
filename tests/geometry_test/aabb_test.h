#pragma once
#include "geometry/geometry.hpp"

//using namespace cgm::geometry;

class aabb_test
{
public:
	
	aabb_test();
	void print_test() {
		using namespace cgm::geometry;
		AABB3<float> aabb3A;
		aabb3A.print();
	}

	void add_test() {
		using namespace cgm::geometry;
		std::array<float, 3> arr1A = { 1.1f,2.2f,3.3f };
		Point3<float> pointA = Point3<float>(arr1A);
		std::array<float, 3> arr1B = { -1.1f,4.2f,2.3f };
		Point3<float> pointB = Point3<float>(arr1B);
		AABB3<float> aabb3A;
		aabb3A.add(pointA);
		aabb3A.print();
		aabb3A.add(pointB);
		aabb3A.print();
	}

private:

};

aabb_test::aabb_test()
{
	//print_test();
	add_test();
}