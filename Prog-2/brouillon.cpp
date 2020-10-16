#include <utility>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class Nombre {

public:
    // Constructeur par défaut
    Nombre(){
        *premier_ = 0;
    }
    

    // Constructeur par défaut
    Nombre( unsigned long n ){
        *premier_ = Chiffre(n);
    }

    // Constructeur de copie
    Nombre(const Nombre & n){
        premier_ = n.premier_;
    }

    // Destructeur
    ~Nombre(){}

    void addFront(unsigned long chiffre);

    // Opérateur d'affectation
    Nombre & operator=( const Nombre & n ){
        premier_ = new Chiffre(*n.premier_);
        return *this;
    }
    
    friend std::ostream & operator << ( std::ostream & out, const Nombre & n );
    friend std::istream & operator >> ( std::istream & in, Nombre & n );

// private:
    struct Chiffre {
        unsigned int chiffre_;     // entre 0 et 9
        Chiffre * suivant_;        // chiffre de poids supérieur ou nullptr
        std::ostream & affiche(std::ostream & out) const;
        Chiffre( unsigned long n ){
            chiffre_ = static_cast< unsigned int >( n % 10 );
            suivant_ = ( n > 9 ) ? new Chiffre(n/10) : nullptr ;
        }
        Chiffre( const Chiffre & c){
            chiffre_ = c.chiffre_ ;
            suivant_ = c.suivant_ ? new Chiffre(*c.suivant_) : nullptr ;
        }
    };
    Chiffre * premier_;


};

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

void Nombre::addFront(unsigned long chiffre){
    Chiffre * ch = new Chiffre(chiffre);
    ch->suivant_ = premier_;
    premier_ = ch;
}

std::istream & operator >> ( std::istream & in, Nombre & n )
{
    // in est le flux d'entrée
    delete n.premier_;
    n.premier_ = nullptr;
    while( in.good() ) {
        int c;
        c = in.get();
        if( std::isdigit( c )) {
            unsigned long d;
            d = static_cast<unsigned long>( c - '0' );  // d contient le chiffre entre 0 et 9 qui vient d'être lu
            n.addFront(d);
        }
    else break;
    }
    return in;
}
   
int main(){
    Nombre n(1);
    std::cin >> n;
    // std::string big{ "123456789123456789123456789123456789" };
    // std::istringstream in{big} ;
    // in = big ;
    // Nombre n;
    // in >> n;
    return 0;
}