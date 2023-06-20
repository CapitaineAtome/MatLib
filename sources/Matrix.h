#ifndef MATLIB_MATRIX_H
#define MATLIB_MATRIX_H

#include <cstdint>
#include <concepts>
#include <cassert>
#include <algorithm>

template<typename T>
concept IsValidMatrixType = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};

template<typename Type, const size_t Lines, const size_t Cols>
requires IsValidMatrixType<Type>
class Matrix {
public:
    explicit Matrix(const Type init_value = {}) {

        for(auto &lines : mat) {

            for(auto &elem: lines) {

                elem = init_value;
            }
        }
    }

    template<typename T, const size_t L, const size_t C>
    explicit Matrix(const Matrix<T, L, C> &other) {

        for(size_t i{}; i < std::min(Lines, L); ++i) {
            for(size_t j{}; j < std::min(Cols, C); ++j) {

                mat[i][j] = other(i, j);
            }
        }
    }

    constexpr size_t lines() const noexcept {

        return Lines;
    }

    constexpr size_t columns() const noexcept {

        return Cols;
    }

    constexpr Type &operator()(const size_t l, const size_t c) {

        assert(l < Lines);
        assert(c < Cols);

        return mat[l][c];
    }

    constexpr Matrix operator+(const Type k) const {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) += k;
            }
        }

        return temp;
    }

    constexpr Matrix operator-(const Type k) {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) -= k;
            }
        }

        return temp;
    }

    constexpr Matrix operator*(const Type k) {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) *= k;
            }
        }

        return temp;
    }

    constexpr Matrix operator/(const Type k) {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) /= k;
            }
        }

        return temp;
    }

    constexpr Matrix operator+(Matrix other) {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) += other(i, j);
            }
        }

        return temp;
    }

    constexpr Matrix operator-(Matrix other) {
        Matrix temp = *this;

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < Cols; ++j) {

                temp(i, j) -= other(i, j);
            }
        }

        return temp;
    }

    template<const size_t L, const size_t C>
    requires (Lines == C)
    constexpr Matrix<Type, Lines, C> operator*(Matrix<Type, L, C> other) {
        Matrix<Type, Lines, C> temp{};

        for(size_t i = 0; i < Lines; ++i) {
            for(size_t j = 0; j < C; ++j) {

                temp(i, j) = this->operator()(i, j) * other(j, i);
            }
        }

        return temp;
    }

protected:
    Type mat[Lines][Cols];
};
#endif // MATLIB_MATRIX_H
