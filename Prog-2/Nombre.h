#include <iostream>
#include <string>
#include <cctype>

//Pour les class

class Nombre {

public:
    // Constructeur par défaut
    Nombre(){
        premier_ = new Chiffre(0);
    }
    

    // Constructeur par défaut
    Nombre( unsigned long n ){
        premier_ = new Chiffre(n);
    }

    // Constructeur de copie
    Nombre( const Nombre & n ) : premier_{ new Chiffre( *n.premier_ )} {}


    // Destructeur
    ~Nombre() { delete premier_; }

    void pop(unsigned int d);

    // Opérateur d'affectation
    Nombre & operator=( const Nombre & n ){
        premier_ = new Chiffre(*n.premier_);
        return *this;
    }
    
    friend std::ostream & operator << ( std::ostream & out, const Nombre & n );
    friend std::istream & operator >> ( std::istream & in, Nombre & n );

    friend Nombre & operator +=( Nombre & n, unsigned int i);
    friend Nombre & operator *=( Nombre & n, unsigned int i);

    Nombre operator+(unsigned int i);
    Nombre operator*(unsigned int i);

private:
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


/*
        Chiffre( unsigned long n )
            : chiffre_{static_cast< unsigned int >( n% 10)}
            , suivant_{( n > 9 ) ? new Chiffre(n/10) : nullptr}
            {}



*/
