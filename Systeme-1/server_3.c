#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool
#include <sys/types.h> // wait()
#include <sys/wait.h> // wait()

bool running = 1;

void stop_handler( int sig )
{
    printf("\n Signal %d reçu.\n", sig);
    int running = 0;
    return;
}

void exit_message()
{
    printf("Exit Message ! \n");
}


struct sigaction act;



int main()
{
    printf("Avant la boucle...\n");
    act.sa_handler = stop_handler;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL); 
    sigaction(SIGKILL, &act, NULL);

    int pid=fork();  // creer deux process

	if (pid < 0) 
    {
        printf("error in fork!"); 
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) 
    {
		// printf("Je suis le fils. mon id est %d\n", getpid());
        while(running)
        {
            printf("Je suis le fils. mon id est %d\n", getpid());
            printf("Je suis le fils. pere id est %d\n", getppid());
            printf("nombre aleatoire = %d\n", rand() % 100);
            sleep(2);
        }
        exit(0);
    }
    else 
    {
		// printf("Je suis le pere. mon id est %d\n", getpid());
        while(running)
        {
            printf("Je suis le pere. mon id est %d\n", getpid());
            printf("Je suis le pere. pere id est %d\n", getppid());
            printf("nombre aleatoire = %d\n", rand() % 100);
            sleep(2);
        }
        wait(NULL); 
        exit(0);
    }

    // sigaction(SIGINT, &act, NULL);  // SIGINT; ^C affiche le message
    // sigaction(SIGTERM, &act, NULL); // SIGTERM; kill <pid> affiche le message
    // sigaction(SIGKILL, &act, NULL);// SIGKILL;  kill -9 <pid> affiche le message
    

    // while(running)
    // {
    //     printf("pid = %d\n", getpid());
    //     printf("ppid = %d\n", getppid());
    //     printf("nombre aleatoire = %d\n", rand() % 100);
    //     sleep(1);
    // }
    printf("Apres la boucle...\n");
    atexit(exit_message);
    return EXIT_SUCCESS;
}

//*********************************************************
/*

2.1 Même code
fork() ==> On peut distinguer les codes de pères et de fils en suivant le numéro <pid>.

Après kill le fils ==> le père continue l'execution, avec ps a on voit qu'avant il y a deux server_3 en execution, après il ne reste qu'un.

Relance, kill le pere ==> le fils continue l'execution, mais son ppid devient 1.

wait()
^C ==> les deux s'arretent
kill <pid> ==> le pere commencent l'execution
kill -9 <pid> ==> le pere commencent l'execution



*/




//*********************************************************
/*Brouillon

        while(running)
        {
            printf("Je suis le pere. mon id est %d\n", getpid());
            printf("Je suis le pere. pere id est %d\n", getppid());
            printf("nombre aleatoire = %d\n", rand() % 100);
            sleep(1);
        }

        sigaction(SIGINT, &act, NULL);  // SIGINT; ^C affiche le message
        sigaction(SIGTERM, &act, NULL); // SIGTERM; kill <pid> affiche le message
        sigaction(SIGKILL, &act, NULL);// SIGKILL;  kill -9 <pid> affiche le message

        while(running)
        {
            printf("Je suis le fils. mon id est %d\n", getpid());
            printf("Je suis le fils. pere id est %d\n", getppid());
            printf("nombre aleatoire = %d\n", rand() % 100);
            sleep(1);
        }
            
        sigaction(SIGINT, &act, NULL);  // SIGINT; ^C affiche le message
        sigaction(SIGTERM, &act, NULL); // SIGTERM; kill <pid> affiche le message
        sigaction(SIGKILL, &act, NULL);// SIGKILL;  kill -9 <pid> affiche le message


*/

