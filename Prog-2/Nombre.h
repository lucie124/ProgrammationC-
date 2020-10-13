#include <ostream>


//Pour les class


class Nombre {
public:
    Nombre();
    Nombre( unsigned long n );
    ~Nombre();
 
    friend std::ostream & operator <<( std::ostream & out, const Nombre & n );
 
private:
    struct Chiffre {
        unsigned int chiffre_;     // entre 0 et 9
        Chiffre * suivant_;        // chiffre de poids supérieur ou nullptr
    };
    Chiffre * premier_;
};