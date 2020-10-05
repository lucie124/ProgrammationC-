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
#include <time.h>

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

    // create FIFO
    const char * fifo_name = "FIFO_5";
    int pipe_fd = -1;
    int res = 0;
    char str[10];
    // char buffer[10];

    if (access(fifo_name, F_OK) == -1)
    {
        res = mkfifo(fifo_name, 0777);
        if (res != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);
            exit(EXIT_FAILURE);
        }
    }

    pipe_fd = open(fifo_name, O_WRONLY);

    printf("Je suis server. mon id est %d\n", getpid());

    while(running)
    {
        srand(time(NULL));
        int a = rand()%100;
        sprintf(str,"%d",a);
        printf("Data envoyé : %s\n",str);
        char * msg = str;
        write(pipe_fd, msg, strlen(msg));
        sleep(2);
    }
    close(pipe_fd);

    printf("Apres la boucle...\n");
    atexit(exit_message);
    return EXIT_SUCCESS;
}
