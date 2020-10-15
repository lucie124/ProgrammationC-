#include "Nombre.h"
// #include <istream>
// #include <iostream>
// #include <string>
// #include <cctype>

//Pour les fonctions

std::ostream & operator << ( std::ostream & out, const Nombre & n )
{
    if( n.premier_ ) n.premier_ -> affiche(out);
    return out;
}

std::ostream & Nombre::Chiffre::affiche( std::ostream & out) const
{
    if( suivant_ ) suivant_ -> affiche(out);
    return out << chiffre_;
}


std::istream & operator >> ( std::istream & in, Nombre & n )
{
    // in est le flux d'entrée
    n.premier_ = nullptr;
    while( in.good() ) {
        int c{ in.get() };
        if( std::isdigit( c )) {
            unsigned int d{ static_cast<unsigned int>( c - '0' )};  // d contient le chiffre entre 0 et 9 qui vient d'être lu
            Nombre::Chiffre chiffre = Nombre::Chiffre{d};
            chiffre.suivant_ = n.premier_;
            * n.premier_ = chiffre;
            /* Creation de nombre qui ne marche pas
            Nombre newNb = Nombre(d);
            newNb.premier_->suivant_ = n.premier_;
            n.premier_ = newNb.premier_;
            */
        }
    else break;
    }
    return in;
}

// int main()
// {
//     return 0;
// }
