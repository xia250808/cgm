#pragma once
#include "geometry/geometry.hpp"

using namespace cgm::geometry;

class triangle_test
{
public:
	triangle_test();
	void print_test() {
		std::array<float, 3> arr1A = { 1.1f,2.2f,3.3f };
		Point3<float> pointA = Point3<float>(arr1A);
		std::array<float, 3> arr1B = { -1.1f,4.2f,2.3f };
		Point3<float> pointB = Point3<float>(arr1B);
		std::array<float, 3> arr1C = { -1.1f,5.2f,5.3f };
		Point3<float> pointC = Point3<float>(arr1C);
		Triangle<float> triangleA = Triangle<float>(pointA, pointB, pointC);
		triangleA.print();
	}

	void area_test() {
		Point3<float> pointA = { { 0,0,0 } };
		Point3<float> pointB = { { 0,3,0 } };
		Point3<float> pointC = { { 4,0,0 } };
		Triangle<float> triangleA = Triangle<float>({ {pointA, pointB, pointC} });
		triangleA.print();
		std::cout<<triangleA.area();
	}

	void isValid_test() {
		Point3<float> pointA = { { 0,0,0 } };
		Point3<float> pointB = { { 0,3,0 } };
		Point3<float> pointC = { { 0,5,0 } };
		Triangle<float> triangleA = Triangle<float>({ {pointA, pointB, pointC} });
		std::cout << triangleA.isValid();
		std::cout<<triangleA.area();
	}

	void barycentric() {
		Point3<float> pointA = { { 1,0,0 } };
		Point3<float> pointB = { { 0,2,0 } };
		Point3<float> pointC = { { 0,0,1 } };
		Point3<float> pointD = { { 0,5,0 } };
		Triangle<float> triangleA = Triangle<float>({ {pointA, pointB, pointC} });
		Vec3<float> barycentric_coordinates = calculate::barycentricCoordinates(triangleA, pointD);
		barycentric_coordinates.print();
	}

private:

};

triangle_test::triangle_test()
{
	//print_test();
	//isValid_test();
	//area_test();
	barycentric();
}