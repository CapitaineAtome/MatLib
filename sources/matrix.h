#ifndef MATLIB_MATRIX_H
#define MATLIB_MATRIX_H

#include <cassert>
#include <cstdint>

#include <concepts>
#include <algorithm>
#include <array>

namespace matlib {
    
    template< typename T >
    concept is_valid_matrix_type = requires( T a,
                                             T b ) {
        a + b;
        a - b;
        a * b;
        a / b;
    };
    
    template< typename Type, const size_t Lines, const size_t Cols >
    requires is_valid_matrix_type< Type >
    class matrix {
    public:
        explicit matrix( const Type init_value ) {
            
            for( auto &line: mat ) {
                
                for( auto &elem: line ) {
                    
                    elem = init_value;
                }
            }
        }
        
        explicit matrix( const std::array< std::array< Type, Lines >, Cols > &init_array ) {
            
            for( size_t i {}; i < Lines; ++i ) {
                
                for( size_t j {}; j < Cols; ++j ) {
                    
                    mat[ i ][ j ] = init_array[ i ][ j ];
                }
            }
        }
        
        template< typename T, const size_t L, const size_t C >
        explicit matrix( const matrix< T, L, C > &other ) {
            
            for( size_t i {}; i < std::min( Lines, L ); ++i ) {
                for( size_t j {}; j < std::min( Cols, C ); ++j ) {
                    
                    mat[ i ][ j ] = other( i, j );
                }
            }
        }
        
        [[nodiscard]] constexpr size_t lines() const noexcept {
            
            return Lines;
        }
        
        [[nodiscard]] constexpr size_t columns() const noexcept {
            
            return Cols;
        }
        
        constexpr Type &operator()( const size_t l,
                                    const size_t c ) {
            
            assert( l < Lines );
            assert( c < Cols );
            
            return mat[ l ][ c ];
        }
        
        constexpr Type get( const size_t l,
                            const size_t c ) const {
            
            assert( l < Lines );
            assert( c < Cols );
            
            return mat[ l ][ c ];
        }
        
        constexpr matrix operator+( const Type k ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) += k;
                }
            }
            
            return temp;
        }
        
        constexpr matrix operator-( const Type k ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) -= k;
                }
            }
            
            return temp;
        }
        
        constexpr matrix operator*( const Type k ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) *= k;
                }
            }
            
            return temp;
        }
        
        constexpr matrix operator/( const Type k ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) /= k;
                }
            }
            
            return temp;
        }
        
        constexpr matrix operator+( const matrix &other ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) += other.get( i, j );
                }
            }
            
            return temp;
        }
        
        constexpr matrix operator-( const matrix &other ) const noexcept {
            
            matrix temp = *this;
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < Cols; ++j ) {
                    
                    temp( i, j ) -= other.get( i, j );
                }
            }
            
            return temp;
        }
        
        template< const size_t L, const size_t C >
        requires (Lines == C)
        constexpr matrix< Type, Lines, C > operator*( matrix< Type, L, C > other ) const noexcept {
            
            for( size_t i = 0; i < Lines; ++i ) {
                for( size_t j = 0; j < C; ++j ) {
                    
                    other( j, i ) *= this->get( i, j );
                }
            }
            
            return other;
        }
    
    protected:
        std::array< std::array< Type, Lines >, Cols > mat;
    };
    
    template< typename Tm, typename Tk, const size_t Lines, const size_t Cols >
    constexpr matrix< Tm, Lines, Cols > operator+( const Tk k,
                                                   const matrix< Tm, Lines, Cols > &matrix ) noexcept {
        
        return matrix + k;
    }
    
    template< typename Tm, typename Tk, const size_t Lines, const size_t Cols >
    constexpr matrix< Tm, Lines, Cols > operator-( const Tk k,
                                                   const matrix <Tm, Lines, Cols> &matrix ) noexcept {
        
        return matrix - k;
    }
    
    template< typename Tm, typename Tk, const size_t Lines, const size_t Cols >
    constexpr matrix< Tm, Lines, Cols > operator*( const Tk k,
                                                   const matrix <Tm, Lines, Cols> &matrix ) noexcept {
        
        return matrix * k;
    }
    
    template< typename Tm, typename Tk, const size_t Lines, const size_t Cols >
    constexpr matrix< Tm, Lines, Cols > operator/( const Tk k,
                                                   const matrix <Tm, Lines, Cols> &matrix ) noexcept {
        
        return matrix / k;
    }
}
#endif // MATLIB_MATRIX_H
