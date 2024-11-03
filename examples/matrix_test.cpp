#include "matrix.h"

using namespace matlib;

#include <cmath>

constexpr auto rad_to_deg { 57.295779f };


void complementary_filter( matrix<float, 3, 1> &acc,
                           matrix<float, 3, 1> &gyr,
                           matrix<float, 3, 1> &mag,
                           matrix<float, 3, 1> &angle,
                           const float p,
                           const float dt) {
    
    static matrix< float, 3, 1 > Ow { 0.0f };
    
    const auto Oam { matrix<float, 3, 1>{ {std::atan2( acc(0, 0), acc(1, 0) ),
                                          std::atan2( -acc(0, 0), std::sqrt( acc(1, 0) * acc(1, 0) + acc(2, 0) * acc(2, 0) ) ),
                                          0.0f } } };
    
    Ow = Ow + gyr * dt;
    
    angle = ( p * Ow + ( 1 - p ) * Oam ) * rad_to_deg;
}

/*void complementary_filter( vector< float, 3 > &acc,
                           vector< float, 3 > &gyr,
                           vector< float, 3 > &mag,
                           vector< float, 3 > &angle,
                           const float p,
                           const float dt ) {
    
    static vector3< float > Ow { 0.0f };
    
    vector3< float > Oam { std::atan2( acc.y, acc.z ),
                           std::atan2( -acc.x, std::sqrt( ( acc.x * acc.x ) + ( acc.z * acc.z ) ) ),
                           0.0f
    };
    
    Oam.z = std::atan2( mag.x * std::sin( Oam.y ) - mag.y * std::cos( Oam.y ),
                        mag.x * std::cos( Oam.x ) + std::sin( Oam.x ) * ( mag.y * std::sin( Oam.y ) + mag.z * std::cos( Oam.y ) ) );
    
    Ow.x += gyr.x * dt;
    Ow.y += gyr.y * dt;
    Ow.z += gyr.z * dt;
    
    angle = { { ( p * Ow.x + ( 1.0f - p ) * Oam.x ) * rad_to_deg,
                ( p * Ow.y + ( 1.0f - p ) * Oam.y ) * rad_to_deg,
                ( p * Ow.z + ( 1.0f - p ) * Oam.z ) * rad_to_deg } };
    
    //    std::array< float, 3 > Oam { std::atan2( acc[ 1 ], acc[ 2 ] ),
    //                                 std::atan2( -acc[ 0 ], sqrt( ( acc[ 1 ] * acc[ 1 ] ) + ( acc[ 2 ] * acc[ 2 ] ) ) ),
    //                                 0.0f };
    //
    //    Oam[ 2 ] = std::atan2( mag[ 2 ] * std::sin( Oam[ 1 ] ) - mag[ 1 ] * std::cos( Oam[ 1 ] ),
    //                           mag[ 0 ] * std::cos( Oam[ 0 ] + std::sin( Oam[ 0 ] ) * ( mag[ 1 ] * std::sin( Oam[ 1 ] + mag[ 2 ] * std::cos( Oam[ 1 ] ) ) ) ) ) );
    //
    //    std::array< float, 3 > Ow { angle[ 0 ] + ( gyr[ 0 ] * dt / 1000.0f ),
    //                                angle[ 1 ] + ( gyr[ 1 ] * dt / 1000.0f ),
    //                                angle[ 2 ] + ( gyr[ 2 ] * dt / 1000.0f ) };
    //
    //    angle = { ( p * Ow[ 0 ] ) + ( ( 1 - p ) * Oam[ 0 ] * rad_to_deg ),
    //              ( p * Ow[ 1 ] ) + ( ( 1 - p ) * Oam[ 1 ] * rad_to_deg ),
    //              ( p * Ow[ 2 ] ) + ( ( 1 - p ) * Oam[ 2 ] * rad_to_deg ) };
}*/

int main() {

    const matrix<double, 2, 3> A{ 1 };
    const matrix<double, 3, 2> B{ 2 };

    auto C0 = A + 3.14;
    auto C1 = A - 3.14;
    auto C2 = A * 3.14;
    auto C3 = A / 3.14;

    auto v = C0(0, 0);

    matrix<char, 2, 2> C{ 0 };

    // auto C4 = A * B;

    auto theta_acc = matrix<double, 1, 3>{ 0 };
    auto theta_gyr = matrix<double, 1, 3>{ { 1, 2, 3 } };
    float alpha = 0.5;
    float dt = 0.01;
    auto angle = theta_gyr * alpha * dt + theta_acc * ( 1 - alpha );
    auto anglea = alpha * theta_gyr * dt + ( 1 - alpha ) * theta_acc;

    return 0;
}
