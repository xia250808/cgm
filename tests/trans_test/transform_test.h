#include "transform/transform.hpp"

class transform_test
{
public:
	transform_test() {
		cgm::trans::TransformFactory<float>::print();

	};


	~transform_test();

private:

};
transform_test::~transform_test()
{
}