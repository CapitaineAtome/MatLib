#include "Matrix.h"

int main() {

    Matrix<char, 2, 3> A{1};
    Matrix<char, 3, 2> B{2};

    auto C0 = A + 3.14;
    auto C1 = A - 3.14;
    auto C2 = A * 3.14;
    auto C3 = A / 3.14;

    Matrix<char, 2, 2> C{};

    // auto C4 = A * B;
    return 0;
}