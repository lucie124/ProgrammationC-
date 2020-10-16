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
	n = n + i;
    return n;
}


Nombre Nombre::operator+(unsigned int i){
    Chiffre * curr = premier_;
    unsigned int val = curr->chiffre_;
    unsigned long sum = 0, carry = i;
    while (carry>0 && curr->suivant_){
        sum = val + carry;
        curr->chiffre_ = sum % 10;
        curr = curr->suivant_;
        val = curr->chiffre_;
        carry = sum / 10;
    };
    sum = val + carry;
    curr->chiffre_ = sum % 10;
    carry = sum / 10;
    if (carry>0)
    {
        curr->suivant_ = new Chiffre(carry);
    }
    return * this;
}

// Nombre & operator *=( Nombre & n, unsigned int i){
//     n = n * i;
//     return n;
// }


// Nombre Nombre::operator*(unsigned int i){
//     Nombre mul(0);
//     Chiffre * curr = premier_;
//     unsigned int val;
//     while (curr)
//     {
//         val = curr->chiffre_;
//         for(int k = 0; k<i;k++){
//             mul += val;
//         }
//         curr = curr->suivant_;
//     }
//     return mul;
// }




// int main()
// {
//     return 0;
// }

            // Nombre newNb = Nombre(d);
            // newNb.premier_->suivant_ = n.premier_;
            // n.premier_ = newNb.premier_;


    // unsigned int val1 = curr->chiffre_;
    // unsigned long sum = 0, carry = i;
    // sum = val1+ carry;
    // ch->chiffre_ = sum % 10;
    // curr = curr->suivant_;
    // carry = sum / 10;
    // while (carry>0 && curr->suivant_)
    // {		
    //     val1 = curr->chiffre_;	
    //     sum = val1 + carry;
    //     ch->suivant_ = new Chiffre(sum % 10);
    //     ch = ch->suivant_;
    //     curr = curr->suivant_;
    //     carry = sum / 10;
    // }  