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

void Nombre::pop(unsigned int d){
    Chiffre ch = Chiffre{d};
    ch.suivant_ = premier_;
    premier_ = new Chiffre(ch);
}

std::istream & operator >> ( std::istream & in, Nombre & n )
{
    // in est le flux d'entrée
    n.premier_ = nullptr;
    while( in.good() ) {
        int c{ in.get() };
        if( std::isdigit( c )) {
            unsigned int d{ static_cast<unsigned int>( c - '0' )};  // d contient le chiffre entre 0 et 9 qui vient d'être lu
            n.pop(d);
            // Nombre::Chiffre chiffre = Nombre::Chiffre{d};
            // chiffre.suivant_ = n.premier_;
            // n.premier_ = new Nombre::Chiffre(chiffre);            
        }
        else break;
    }
    return in;
}


Nombre & operator +=( Nombre & n, unsigned int i){
		n = n+i;
    return n;
}


Nombre Nombre::operator+(unsigned int i){
    Chiffre * curr = premier_;
    unsigned int val = curr->chiffre_;
    unsigned long sum = 0, carry = i;
    while (carry>0 && curr){
        sum = val+ carry;
        curr->chiffre_ = sum % 10;
        curr = curr->suivant_;
        val = curr->chiffre_;
        carry = sum / 10;
    }

    if (carry>0)
    {
        curr->suivant_ = new Chiffre(carry);
    }
    return * this;
}

Nombre & operator *=( Nombre & n, unsigned int i){
    return n;
}


// Nombre Nombre::operator*(unsigned int i){

// }




// int main()
// {
//     return 0;
// }

            // Nombre newNb = Nombre(d);
            // newNb.premier_->suivant_ = n.premier_;
            // n.premier_ = newNb.premier_;
