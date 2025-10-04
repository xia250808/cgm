#include "math/vec.hpp"

using namespace std;
using namespace cgm::math;
class vec_test {

    public:
        static void vecMultTest() {
            Vec<float, 4>  vecA;
            std::array<float, 4> arr1 = { 1,2,3,4 };
            Vec<float, 4> VecB = Vec(arr1);
            (VecB + 2 * VecB).print();
        }
};