#include <gtest/gtest.h>
#include "Nombre.h"
#include <utility>
#include <sstream>

Nombre factorielle( unsigned int n );

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

TEST( TestNombre, Testaddition )
{
    unsigned int add1 = 15;
    unsigned int add2 = 16;
    Nombre n{ add1 };
    n += add2;
    char str[10];
    sprintf(str,"%d",add1+add2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), str );
}

TEST( TestNombre, Testaddition2Nombre )
{
    unsigned int add1 = 99;
    unsigned int add2 = 1;
    Nombre n{ add1 };
    Nombre n2{ add2 };
    n += n2;
    char str[10];
    sprintf(str,"%d",add1+add2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), str );
}

TEST( TestNombre, Testmultiplication )
{
    unsigned int mul1 = 434556;
    unsigned int mul2 = 256;
    Nombre n{ mul1 };
    n *= mul2;
    char str[10];
    sprintf(str,"%d",mul1*mul2);
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), str );
}

TEST( TestNombre, TestFactorielle123 )
{
    std::ostringstream os;
    os << factorielle( 123 );;
    EXPECT_EQ( os.str(), "12146304367025329675766243241881295855454217088483382315328918161829235892362167668831156960612640202170735835221294047782591091570411651472186029519906261646730733907419814952960000000000000000000000000000" );
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
            
    // unsigned int mul1 = 54;
    // unsigned int mul2 = 10;
    // Nombre n{ mul1 };
    // Nombre n2{ 0 };
    // std::cout << n2 << std::endl;
    // for(int k = 0; k<mul2; k++){
    //     n2 += n;
    //     std::cout << n2 << std::endl;
    // }


    // Nombre n {0};
    // std::cout << n << std::endl;
    // Nombre n2{ 54 };
    // for(int i = 0 ; i < 20 ; i++){
    //     n+=n2;
    //     std::cout << n << std::endl;
    // }
    // return 0;
}