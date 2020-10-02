#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool

bool running = 1;

void stop_handler( int sig )
{
    printf("\n Signal %d reçu.\n", sig);
    running = 0;
    return;
}

struct sigaction act;
// act.sa_handler = stop_handler();
// act.flags = 0;




int main()
{
    printf("Avant la boucle...\n");

    act.sa_handler = stop_handler;
    act.sa_flags = 0;

    sigaction(SIGTERM, &act, NULL); // SIGINT -> SIGTERM;  kill <pid> affiche le message
    

    while(running)
    {
        printf("pid = %d\n", getpid());
        printf("ppid = %d\n", getppid());
        printf("nombre aleatoire = %d\n", rand() % 100);
        sleep(1);
    }
    printf("Apres la boucle...\n");
    return EXIT_SUCCESS;
}