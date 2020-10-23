#include <iostream>
#include <sstream>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
 
/*
 * Générateur de nombres aléatoires
 * Il n'est pas nécessaire de comprendre son fonctionnement
 *
 * Exemple d'utilisation pour une attente de durée aléatoire entre 0 et 50 ms
 *   Random random( 50 );
 *   using milliseconds = std::chrono::duration< int, std::milli >;
 *   std::this_thread::sleep_for( milliseconds( random() ));
 */
class Random {
public:
    explicit Random( int max )
        :  dist_( 0, max )
    {}
 
    int operator()() {
        return dist_( rd_ );
    }
private:
    std::random_device rd_;
    std::uniform_int_distribution< int > dist_;
};
 
/*
 * Classe permettant d'assurer la sérialisation des affichages
 * Version simplifiée de la classe de même nom de C++20
 *
 * Exemple d'utilisation
 *   { osyncstream( std::cout ) << "hellow world"; }
 */
class osyncstream {
public:
    osyncstream( std::ostream & out ) : out_( out ) {}
    // L'affichage se fait uniquement à la destruction de l'objet
    ~osyncstream() { 
        std::lock_guard< std::mutex > l( protect_out_ );
        out_ << saved_.str() << std::endl;
    }
 
    // Mémorisation de ce qu'il faut afficher
    osyncstream & operator<<( const std::string & what ) {
        saved_ << what;
        return *this;
    }
    osyncstream & operator<<( const char * what ) {
        saved_ << what;
        return *this;
    }
    osyncstream & operator<<( int what ) {
        saved_ << what;
        return *this;
    }
private:
    static std::mutex protect_out_;
    std::ostream & out_;
    std::ostringstream saved_;
};
std::mutex osyncstream::protect_out_;
 

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 */


class MessageBox {
public:
    MessageBox( unsigned box_size )
        : box_size_( box_size )
        , box_( box_size_, -1 )
        , put_index_( 0 )
        , get_index_( 0 )
    {}
 
    void put( int message ) {
        // TODO : ajouter les mecanismes de synchronisation
        box_[ put_index_ ] = message;
        put_index_ = ( put_index_ + 1 ) % box_size_;
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        int message = box_[get_index_];
        // Pour détecter les erreurs
        box_[get_index_] = -1;
        get_index_ = ( get_index_ + 1 ) % box_size_;
        return message;
    }
private:
    // FIFO réalisée par un tableau géré en tampon circulaire via 2 indices (dépôt et retrait)
    const unsigned box_size_;
    std::vector< int > box_;
    unsigned put_index_;
    unsigned get_index_;
 
    // TODO : ajouter les objets de synchronisation
};
 



/*
 * Super-classe pour les producteurs et consommateurs
 */
class ProdOrCons {
public:
    ProdOrCons( unsigned name, MessageBox & box, Random & random, unsigned nb_messages )
        : name_( name )
        , box_( box )
        , random_( random )
        , nb_messages_( nb_messages )
    {}
 
    virtual ~ProdOrCons() {}
 
    virtual void operator()() = 0;

    // virtual affiche
 
protected:
    // nom sous la forme d'un entier
    unsigned name_;
    // FIFO ou écrire/lire les messages
    MessageBox & box_;
    // générateur de nombres aléatoires
    Random & random_;
    // nombre de messages à produire ou lire
    const unsigned nb_messages_;
};
 


/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
        
    }
};
 


/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : extraire de box nb_messages avec attente aléatoire entre chaque.
        // Afficher des messages pour suivre l'avancement.
        // Signaler comme erreur l'extraction d'un nombre négatif.
    }
};
 
 