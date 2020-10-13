#include <gtest/gtest.h>
#include "Nombre.h"
#include <utility>
#include <sstream>

TEST( TestNombre, TestNombreVide )
{
    Nombre n;
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNombre, TestNombreNul )
{
    Nombre n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNombre, TestNombre12345678 )
{
    Nombre n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}


int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}