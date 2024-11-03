#ifndef VECLIB_VECTOR_H
#define VECLIB_VECTOR_H

#include <cstdint>
#include <concepts>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <array>

namespace matlib {
    
    template< typename T >
    concept is_valid_vector_type = requires( T a,
                                             T b ) {
        a + b;
        a - b;
        a * b;
        a / b;
    };
    
    enum class vector_type {
        ROW,
        COLUMN,
    };
    
    template< typename Type, const size_t Dimension, const vector_type vT > requires is_valid_vector_type< Type >
    class vector {
    public:
        explicit vector( const Type init_value = {} ) {
            
            for( auto &elem: vec ) {
                elem = init_value;
            }
        }
        
        explicit vector( const std::array< Type, Dimension > init_array ) {
            
            size_t    i {};
            for( auto &elem: init_array ) {
                vec[ i++ ] = elem;
            }
        }
        
        template< typename T, const size_t D >
        explicit vector( vector< T, D, vT > &other ) {
            
            for( size_t i {}; i < std::min( Dimension, D ); ++i ) {
                vec[ i ] = other( i );
            }
        }
        
        constexpr vector_type type() const noexcept {
            
            return vT;
        }
        
        constexpr Type get( const size_t idx ) const noexcept {
            
            assert( idx < Dimension );
            
            return vec[ idx ];
        }
        
        constexpr size_t dimension() const noexcept {
            
            return Dimension;
        }
        
        constexpr auto transpose() const noexcept {
            
            if constexpr( vT == vector_type::ROW ) {
                
                vector< Type, Dimension, vector_type::COLUMN > tmp;
                
                for( size_t i {}; i < Dimension; i++ ) {
                    
                    tmp( i ) = get( i );
                }
                
                return tmp;
                
            } else {
                
                vector< Type, Dimension, vector_type::ROW > tmp;
                
                for( size_t i {}; i < Dimension; i++ ) {
                    
                    tmp( i ) = get( i );
                }
                
                return tmp;
            }
        }
        
        constexpr auto magnitude() const noexcept {
            
            auto sum_ = Type {};
            
            for( const auto &elem: vec ) {
                
                sum_ += elem * elem;
            }
            
            return std::sqrt( sum_ );
        }
        
        constexpr vector normal() const noexcept {
            
            vector< Type, Dimension, vT > tmp {};
            auto                          norm_ { magnitude() };
            
            for( size_t i {}; i < Dimension; i++ ) {
                
                tmp( i ) = get( i ) / norm_;
            }
            
            return tmp;
        }
        
        constexpr void normalize() noexcept {
            
            auto norm_ { magnitude() };
            
            for( auto &elem: vec ) {
                
                elem /= norm_;
            }
        }
        
        constexpr Type dot( const vector &vect ) const noexcept {
            
            auto sum_ = Type {};
            
            for( size_t i {}; i < Dimension; i++ ) {
                
                sum_ += get( i ) * vect.get( i );
            }
            
            return sum_;
        }
        
        constexpr friend std::ostream &operator<<( std::ostream &os,
                                                   const vector &vect ) {
            
            for( size_t i {}; i < Dimension; i++ ) {
                
                if( i > 0 ) {
                    if( vT == vector_type::ROW ) {
                        os << ",";
                    } else {
                        os << "\n";
                    }
                }
                
                os << vect.get( i );
            }
            
            return os;
        }
        
        constexpr Type &operator()( const size_t idx ) noexcept {
            
            assert( idx < Dimension );
            
            return vec[ idx ];
        }
        
        constexpr vector operator+( const Type k ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) += k;
            }
            
            return temp;
        }
        
        constexpr vector operator-( const Type k ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) -= k;
            }
            
            return temp;
        }
        
        constexpr vector operator*( const Type k ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) *= k;
            }
            
            return temp;
        }
        
        constexpr vector operator/( const Type k ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) /= k;
            }
            
            return temp;
        }
        
        constexpr vector &operator+=( const Type k ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) += k;
            }
            
            return *this;
        }
        
        constexpr vector &operator-=( const Type k ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) -= k;
            }
            
            return *this;
        }
        
        constexpr vector &operator*=( const Type k ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) *= k;
            }
            
            return *this;
        }
        
        constexpr vector &operator/=( const Type k ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) /= k;
            }
            
            return *this;
        }
        
        template< is_valid_vector_type T >
        constexpr vector operator+( vector< T, Dimension, vT > &other ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) += other( i );
            }
            
            return temp;
        }
        
        constexpr vector operator-( vector &other ) const noexcept {
            
            vector temp = *this;
            
            for( size_t i = 0; i < Dimension; ++i ) {
                temp( i ) -= other( i );
            }
            
            return temp;
        }
        
        constexpr vector &operator+=( vector &other ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) += other( i );
            }
            
            return *this;
        }
        
        constexpr vector &operator-=( vector &other ) noexcept {
            
            for( size_t i = 0; i < Dimension; ++i ) {
                this->operator()( i ) -= other( i );
            }
            
            return *this;
        }
    
    protected:
        Type vec[Dimension];
        
    };
}

#endif //VECLIB_VECTOR_H
