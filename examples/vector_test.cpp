#include "Vector.h"

int main() {

    Vector<double, 2, VectorType::ROW> vA{{-5, -6}};
    Vector<double, 2, VectorType::ROW> vB{2};
    Vector<double, 5, VectorType::COLUMN> vC{{1, 2, 3, 4, 5}};
    auto vD = vC.transpose();

    auto vR1 = vA + vB;

    std::cout << vA << std::endl;
    std::cout << vA.magnitude() << std::endl;
    std::cout << vA.unit().magnitude() << std::endl;
    vA.normalize();
    std::cout << vA << std::endl;
    std::cout << "--------\n";
    std::cout << vB << std::endl;
    std::cout << "--------\n";
    std::cout << vA + vB << std::endl;
    std::cout << "--------\n";
    std::cout << vC * 2 << std::endl;
    std::cout << vD * 2 << std::endl;

    // auto vE = vA * vC;

    return 0;
}
