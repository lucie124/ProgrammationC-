#include <gtest/gtest.h>
#include "Nombre.h"
#include <utility>
#include <sstream>


TEST( TestNombre, TestNombreVide_Defaut )
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

TEST( TestNombre, TestConstructionCopy )
{
    Nombre n{ 246854 };
    Nombre n2 = Nombre(n);
    std::ostringstream os;
    os << n2;
    EXPECT_EQ( os.str(), "246854" );
}

TEST( TestNombre, TestOpAffectCopy )
{
    Nombre n{ 13579 };
    Nombre n2 = n;
    std::ostringstream os;
    os << n2;
    EXPECT_EQ( os.str(), "13579" );
}

TEST( TestNombre, TestLectureGrandNombre )

{
    std::string big{ "123456789123456789123456789123456789" };
    std::istringstream in{ big };
    Nombre n;
    in >> n;
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), big );
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}