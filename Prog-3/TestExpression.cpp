#include <sstream>
#include "Expression.hpp"
#include "gtest/gtest.h"
 
TEST( TestDerivation, TestAffichageNombre )
{
    Nombre n( 2 );
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "2" );
}

TEST( TestDerivation, TestAffichageVariable )
{
    const Expression * e = new Variable( "x" );
    std::ostringstream os;
    os << *e;
    EXPECT_EQ(os.str(), "x" );
    delete e;
}
 
TEST( TestDerivation, TestDerivationNombre )
{
    const Expression * e = new Nombre( -2 );
    const Expression * f = e->derive( "x" );
    ASSERT_TRUE( nullptr != f );
    std::ostringstream os;
    os << *f;
    EXPECT_EQ( os.str(), "0" );
    delete e;
    delete f;
}
 
TEST( TestDerivation, TestDerivationVariable )
{
    const Expression * e = new Variable( "x" );
    const Expression * f = e->derive( "x" );
    ASSERT_TRUE( nullptr != f );
    std::ostringstream os1;
    os1 << *f;
    EXPECT_EQ( os1.str(), "1" );
    delete f;
 
    f = e->derive( "y" );
    ASSERT_TRUE( nullptr != f );
    std::ostringstream os2;
    os2 << *f;
    EXPECT_EQ( os2.str(), "0" );
    delete e;
    delete f;
}
 
// TEST( TestDerivation, TestAffichageAddition )
// {
//     const Expression * e = new Addition( new Variable( "x" ), new Nombre( -2 ));
//     std::ostringstream os;
//     os << *e;
//     EXPECT_EQ( os.str(), "(x + -2)" );
//     delete e;
// }
 
// TEST( TestDerivation, TestDerivationAddition )
// {
//     const Expression * e = new Addition( new Variable( "x" ), new Nombre( -10 ));
//     const Expression * f = e->derive( "x" );
//     ASSERT_TRUE( nullptr != f );
//     std::ostringstream os;
//     os << *f;
//     EXPECT_EQ( os.str(), "(1 + 0)" );
//     delete e;
//     delete f;
// }
 
// TEST( TestDerivation, TestAffichageMultiplication )
// {
//     const Expression * e = new Multiplication( new Variable( "y" ), new Variable( "z" ));
//     std::ostringstream os;
//     os << *e;
//     EXPECT_EQ( os.str(), "(y * z)" );
//     delete e;
// }
 
// TEST( TestDerivation, TestDerivationMultiplication )
// {
//     // This test expects (f * g)' = f' * g + f * g'
//     const Expression * e = new Multiplication(
//                          new Variable( "x" ),
//                          new Multiplication( new Variable( "y" ), new Variable( "z" ))
//                      );
//     const Expression * f = e->derive( "x" );
//     ASSERT_TRUE( nullptr != f );
//     std::ostringstream os;
//     os << *f;
//     EXPECT_EQ( os.str(), "((1 * (y * z)) + (x * ((0 * z) + (y * 0))))" );
//     delete e;
//     delete f;
// }



int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();

}