#ifndef VECLIB_VECTOR_H
#define VECLIB_VECTOR_H

#include <cstdint>
#include <concepts>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <array>

template<typename T>
concept IsValidVectorType = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};

enum class VectorType {
    ROW,
    COLUMN,
};

template<typename Type, const size_t Dimension, const VectorType vT>
requires IsValidVectorType<Type>
class Vector {
public:
    explicit Vector(const Type init_value = {}) {

        for(auto &elem : vec) {
                elem = init_value;
        }
    }

    explicit Vector(const std::array<Type, Dimension> init_array) {

        size_t i{};
        for(auto &elem : init_array) {
            vec[i++] = elem;
        }
    }

    template<typename T, const size_t D>
    explicit Vector(Vector<T, D, vT> & other) {

        for(size_t i{}; i < std::min(Dimension, D); ++i) {
                vec[i] = other(i);
        }
    }

    constexpr VectorType type() const noexcept {

        return vT;
    }

    constexpr Type get(const size_t idx) const noexcept {
        assert(idx < Dimension);

        return vec[idx];
    }

    constexpr size_t dimension() const noexcept {
        return Dimension;
    }

    constexpr auto transpose() const noexcept {

        if constexpr(vT == VectorType::ROW) {

            Vector<Type, Dimension, VectorType::COLUMN> tmp;

            for(size_t i{}; i < Dimension; i++) {

                tmp(i) = get(i);
            }

            return tmp;

        } else {

            Vector<Type, Dimension, VectorType::ROW> tmp;

            for(size_t i{}; i < Dimension; i++) {

                tmp(i) = get(i);
            }

            return tmp;
        }
    }

    constexpr auto magnitude() const noexcept {

        auto sum_ = Type{};

        for(const auto & elem : vec) {

            sum_ += elem * elem;
        }

        return std::sqrt(sum_);
    }

    constexpr Vector normal() const noexcept {

        Vector<Type, Dimension, vT> tmp{};
        auto norm_{magnitude()};

        for(size_t i{}; i < Dimension; i++) {

            tmp(i) = get(i) / norm_;
        }

        return tmp;
    }

    constexpr void normalize() noexcept {

        auto norm_{magnitude()};

        for(auto & elem : vec) {

            elem /= norm_;
        }
    }

    constexpr Type dot(const Vector & vect) const noexcept {

        auto sum_ = Type{};

        for(size_t i{}; i < Dimension; i++) {

            sum_ += get(i) * vect.get(i);
        }

        return sum_;
    }

    constexpr friend std::ostream & operator<<(std::ostream & os, const Vector & vect) {

        for(size_t i{}; i < Dimension; i++) {

            if(i > 0) {
                if(vT == VectorType::ROW) {
                    os << ",";
                } else {
                    os << "\n";
                }
            }

            os << vect.get(i);
        }

        return os;
    }

    constexpr Type & operator()(const size_t idx) noexcept {
        assert(idx < Dimension);

        return vec[idx];
    }

    constexpr Vector operator+(const Type k) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) += k;
        }

        return temp;
    }

    constexpr Vector operator-(const Type k) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) -= k;
        }

        return temp;
    }

    constexpr Vector operator*(const Type k) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) *= k;
        }

        return temp;
    }

    constexpr Vector operator/(const Type k) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) /= k;
        }

        return temp;
    }

    constexpr Vector & operator+=(const Type k) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) += k;
        }

        return *this;
    }

    constexpr Vector & operator-=(const Type k) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) -= k;
        }

        return *this;
    }

    constexpr Vector & operator*=(const Type k) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) *= k;
        }

        return *this;
    }

    constexpr Vector & operator/=(const Type k) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) /= k;
        }

        return *this;
    }

    template<IsValidVectorType T>
    constexpr Vector operator+(Vector<T, Dimension, vT> & other) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) += other(i);
        }

        return temp;
    }

    constexpr Vector operator-(Vector & other) const noexcept {
        Vector temp = *this;

        for(size_t i = 0; i < Dimension; ++i) {
            temp(i) -= other(i);
        }

        return temp;
    }

    constexpr Vector & operator+=(Vector & other) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) += other(i);
        }

        return *this;
    }

    constexpr Vector & operator-=(Vector & other) noexcept {

        for(size_t i = 0; i < Dimension; ++i) {
            this->operator()(i) -= other(i);
        }

        return *this;
    }

protected:
    Type vec[Dimension];
    
};

#endif //VECLIB_VECTOR_H
