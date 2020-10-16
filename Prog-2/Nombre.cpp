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


Nombre & operator +=( Nombre & n, Nombre & n2){
    n = n + n2;
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

Nombre Nombre::operator+(Nombre & n){
    // Nombre somme{ 0 };
    Chiffre * curr1 = premier_;
    Chiffre * curr2 = n.premier_;
    unsigned int val1 = curr1->chiffre_;
    unsigned int val2 = curr2->chiffre_;
    unsigned long sum = 0, carry = 0;
    while (curr1->suivant_ && curr2->suivant_){
        sum = val1 + val2 + carry;
        curr1->chiffre_ = sum % 10;
        curr1 = curr1->suivant_;
        curr2 = curr2->suivant_;
        val1 = curr1->chiffre_;
        val2 = curr2->chiffre_;
        carry = sum / 10;
    };
    sum = val1 + val2 + carry;
    curr1->chiffre_ = sum % 10;
    carry = sum / 10;

    if (carry > 0 && curr1->suivant_){
        curr1 = curr1->suivant_;
        val1 = curr1->chiffre_;
        while (curr1->suivant_){
            sum = val1 + carry;
            curr1->chiffre_ = sum % 10;
            curr1 = curr1->suivant_;
            val1 = curr1->chiffre_;
            carry = sum / 10;
        } 
        sum = val1 + carry;
        curr1->chiffre_ = sum % 10;
        carry = sum / 10;
    }

    if (curr2->suivant_){
        curr2 = curr2->suivant_;
        val2 = curr2->chiffre_;
        while (curr2->suivant_)
        {
            sum = val2 + carry;
            curr1->suivant_ = new Chiffre(sum % 10);
            curr1 = curr1->suivant_;
            curr2 = curr2->suivant_;
            val2 = curr2->chiffre_;
            carry = sum / 10;
        }
        sum = val2 + carry;
        curr1->suivant_ = new Chiffre(sum % 10);
        carry = sum / 10;
    }
    
    if (carry>0)
    {
        curr1->suivant_ = new Chiffre(carry);
    }
    return * this;
}


Nombre & operator *=( Nombre & n, unsigned int i){
    n = n * i;
    return n;
}

Nombre Nombre::operator*(unsigned int i){
    Nombre n{0};
    for(int k = 0; k<i; k++){
        n = n + *this;
    }
    return n;
}

/*
Pas d'idée de construire la multiplication sans l'addition de deux nombre,
donc j'ai construit l'addition des nombre pour faire la multiplication.
*/



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