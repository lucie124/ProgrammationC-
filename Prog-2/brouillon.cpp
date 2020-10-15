#include <utility>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
   
int main(){
    std::string big = "123456789123456789123456789123456789";
    std::istringstream in(big);
    while( in.good() ){
        int c = in.get();
        if( std::isdigit( c )){
            unsigned int d =static_cast<unsigned int>( c - '0' );
            // d contient le chiffre entre 0 et 9 qui vient d'être lu
            // ... à vous de l'utiliser ...
            cout << d << endl;
        }
    else break;
    }
    return 0;
}