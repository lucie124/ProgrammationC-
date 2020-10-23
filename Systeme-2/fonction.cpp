#include "class.h"









/*
 * Test avec 1 producteur et 1 consommateur
 */
int main() {
    const unsigned box_size = 2;
    const unsigned nb_messages = 20;
 
    Random random( 50 );
    MessageBox box( box_size );
    Producer producer( 1, box, random, nb_messages );
    Consumer consumer( 1, box, random, nb_messages );
 
    std::cout << "start" << std::endl;
 
    std::thread producer_thread( producer );
    std::thread consumer_thread( consumer );
    producer_thread.join();
    consumer_thread.join();
 
    std::cout << "finish" << std::endl;
 
    return 0;
}