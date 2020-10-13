#include <iostream>


//Pour les class

class Nombre {

public:
    Nombre(){
        *premier_ = 0;
    }

    Nombre( unsigned long n ){
        *premier_ = Chiffre(n);
    }

    ~Nombre(){}
 
    friend std::ostream & operator << ( std::ostream & out, const Nombre & n );


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