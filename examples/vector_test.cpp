#include "vector.h"

using namespace matlib;

int main() {

    vector<double, 2, vector_type::ROW> vA{{-5, -6}};
    vector<double, 2, vector_type::ROW> vB{2};
    vector<double, 5, vector_type::COLUMN> vC{{1, 2, 3, 4, 5}};
    auto vD = vC.transpose();

    auto vR1 = vA + vB;

    std::cout << vA << std::endl;
    std::cout << vA.magnitude() << std::endl;
    std::cout << vA.normal().magnitude() << std::endl;
    vA.normalize();
    std::cout << vA << std::endl;
    std::cout << "--------\n";
    std::cout << vB << std::endl;
    std::cout << "--------\n";
    std::cout << vA + vB << std::endl;
    std::cout << "--------\n";
    std::cout << vC * 2 << std::endl;
    std::cout << vD * 2 << std::endl;

    return 0;
}
