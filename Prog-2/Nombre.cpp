#include "Nombre.h"
#include <iostream>


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

// int main()
// {
//     return 0;
// }
