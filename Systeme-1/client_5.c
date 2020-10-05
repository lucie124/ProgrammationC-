#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool
#include <sys/types.h> // wait()
#include <sys/wait.h> // wait()
#include <string.h> //strlen()
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>   //for mkfifo

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

    //FIFO setting
    const char * fifo_name = "FIFO_5";
    int pipe_fd = -1;
    int res = 0;
    char buffer[10];

    pipe_fd = open(fifo_name, O_RDONLY);

    printf("Je suis client. mon id est %d\n", getpid());

    while(running)
    {
        memset(buffer, '\0', sizeof(buffer));
        // printf("nombre aleatoire = %d\n", rand() % 100);
        int res = read(pipe_fd, buffer, sizeof(buffer));
        if(res ==0){
            close(pipe_fd);
            atexit(exit_message);
            exit(EXIT_FAILURE);
        }
        printf("Data reçu : %s\n", buffer);
        sleep(2);
    }
    close(pipe_fd);

    printf("Apres la boucle...\n");
    atexit(exit_message);
    exit(EXIT_SUCCESS);
}
