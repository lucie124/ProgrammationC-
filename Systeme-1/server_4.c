#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool
#include <sys/types.h> // wait()
#include <sys/wait.h> // wait()
#include <string.h> //strlen()

bool running = 1;

void stop_handler( int sig )
{
    printf("\n Signal %d reçu.\n", sig);
    running = 0;
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

    // create pip
    int fd[2];
    pipe(fd);
    int len;
    char buf[1024];

    if(pipe(fd)<0)
    {
        perror("pipe");
        exit(0);
    }

    int pid=fork();  // creer deux process

	if (pid < 0) 
    {
        printf("error in fork!"); 
        exit(EXIT_FAILURE);
    }

    else if (pid > 0) 
    {
        close(fd[0]);
        while(running)
        {
            printf("Je suis le pere. mon id est %d\n", getpid());
            // printf("nombre aleatoire = %d\n", rand() % 100);
            char *msg ="let's chat with pipe !\n";
            write(fd[1], msg, strlen(msg));
            sleep(2);
        }
        close(fd[1]);
        wait(NULL); 
    }
    else
    {
        close(fd[1]);
        while(running)
        {
            printf("nombre aleatoire = %d\n", rand() % 100);
            printf("Je suis le fils. mon id est %d\n", getpid());
            int len = read(fd[0], buf, sizeof(buf));
            // write(STDOUT_FILENO, buf, len)
            if (len == 0) 
            {
                exit(0); 
            }
            printf("%s\n", buf);
            sleep(2);
        }
        close(fd[0]);
        exit(0);

    }
    printf("Apres la boucle...\n");
    atexit(exit_message);
    return EXIT_SUCCESS;
}



//*********************************************************
/*Brouillon

        while(running)
        {
            printf("Je suis le pere. mon id est %d\n", getpid());
            printf("Je suis le pere. pere id est %d\n", getppid());
            printf("nombre aleatoire = %d\n", rand() % 100);
            sleep(2);
        }

            printf("Je suis le fils. pere id est %d\n", getppid());
*/