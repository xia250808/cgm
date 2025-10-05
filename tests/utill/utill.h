#pragma
#include "math/​math.hpp"
#include <glm/glm.hpp> 
using namespace cgm::math;
class Utill
{
public:
	Utill();
	static Mat<float,3> transGlmMat4ToMat3(const glm::mat4& m) {
		Mat<float, 3> retMat;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j) {
				retMat(i, j) = m[i][j];
			}
		}
		return retMat;
	}
	~Utill();

private:

};
Utill::Utill()
{
}

Utill::~Utill()
{
}