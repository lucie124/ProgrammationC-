// #include "class.h"
#include <iostream>
#include <sstream>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h> 
#include <sys/wait.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include<boost/interprocess/sync/scoped_lock.hpp>
#include<boost/interprocess/sync/interprocess_mutex.hpp>
#include<boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/mapped_region.hpp>
// #include <main>
using namespace std;
using namespace boost::interprocess;


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
 * FIFO d'echange de messages entre producteurs et consommateurs
 */


class MessageBox {
public:
    MessageBox( )
        // : box_size_( box_size )
        // : box_( box_size_, -1 )
        // , put_index_( 0 )
        // , get_index_( 0 )
    {
        for(int i=0; i< box_size_; i++){
            box_[i] = -1;
        }
        put_index_ = 0;
        get_index_ = 0;
    }
 
    void put( int message ) {
        // TODO : ajouter les mecanismes de synchronisation
        unique_lock< mutex > lock( mutex_ );
        while (box_[put_index_] != -1){
            box_not_full_.wait( lock );
        }
        box_[ put_index_ ] = message;
        put_index_ = ( put_index_ + 1 ) % box_size_;
        box_not_empty_.notify_one();
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        unique_lock< mutex > lock( mutex_ );
        while( box_[get_index_]==-1){
            box_not_empty_.wait( lock );
        }
        int message = box_[get_index_];
        // Pour détecter les erreurs
        box_[get_index_] = -1;
        get_index_ = ( get_index_ + 1 ) % box_size_;
        box_not_full_.notify_one();
        return message;
    }
private:
    // FIFO réalisée par un tableau géré en tampon circulaire via 2 indices (dépôt et retrait)
    static const unsigned box_size_ = 2;
    std::array<int, box_size_> box_;
    unsigned put_index_;
    unsigned get_index_;

    // TODO : ajouter les objets de synchronisation
    // unsigned int nb_messages_;
    condition_variable box_not_empty_;
    condition_variable box_not_full_;
    std::mutex mutex_;
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
        for (int i = 0; i < nb_messages_; i++){
            //attente aléatoire
            // Random random(50);
            // using milliseconds = std::chrono::duration< int, std::milli >;
            // std::this_thread::sleep_for( milliseconds( random() ));
            // sleep(2);

            //put message
            int message = rand();
            box_.put(message);
            printf("Producer %d send : %d\n", name_, message);
            // cout << "Producer " << name_ << " send : " << message << endl;
        }
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
        for (int i = 0; i < nb_messages_; i++){
            //attente aléatoire
            Random random(50);
            using milliseconds = std::chrono::duration< int, std::milli >;
            std::this_thread::sleep_for( milliseconds( random() ));
            // sleep(2);

            //get message
            int message = box_.get();

            //print message
            if (message < 0){
                printf("Consumer %d extract error\n", name_);
                // cout << "Consumer " << name_ << " extract error" << endl;
            }
            else{
                printf("Consumer %d receive : %d\n", name_, message);
                // cout << "Consumer " << name_ << " receive : " << message << endl;
            }
        }
    }
};
 
 

int main() {
    // shared_memory_object::remove("shared_memory");

    //Create a shared memory object.
    shared_memory_object shm_obj(
        open_or_create,             //open or create
        "shared_memory",            //name
        read_write                  //read-write mode
    );

    //Set size
    shm_obj.truncate(sizeof(MessageBox));

    //Map the whole shared memory in this process
    mapped_region region (shm_obj, read_write);

    void * addr = region.get_address();
    MessageBox * box = new ( addr ) MessageBox();

    cout << "start" << endl;

    Random random( 50 );
    const unsigned nb_messages = 20;

    int pid = fork();
	if (pid < 0) 
    {
        printf("error in fork!"); 
        exit(EXIT_FAILURE);
    }

    else if (pid > 0) 
    {
        Producer producer( 1, *box, random, nb_messages );
        producer();
        wait(NULL);
        exit(0);
    }

    else{
        Consumer consumer( 1, *box, random, nb_messages );
        consumer();
        shared_memory_object::remove("shared_memory");
        exit(0);
    }
    cout << "finish" << endl;
    return 0;
}