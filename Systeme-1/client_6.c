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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

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

//TCP
#define PORT 13


int main()
{
    printf("Avant la boucle...\n");
    act.sa_handler = stop_handler;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL); 
    sigaction(SIGKILL, &act, NULL);

    //TCP settings
    int SocketFD = 0; 
    unsigned int remoteaddr = 0;
    int connectv = 0;
    struct sockaddr_in RemoteAddr = {0};
    socklen_t socklen = 0;  
    char buffer[10];

    //create socket
    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(SocketFD < 0)
	{
		printf("Create socket failed\n");
		return 0;
	}	

	RemoteAddr.sin_family = AF_INET;
	RemoteAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, "10.57.150.3", &remoteaddr);
	RemoteAddr.sin_addr.s_addr=remoteaddr;

    //connect
    connectv = connect(SocketFD, (void *)&RemoteAddr, sizeof(RemoteAddr));
    if(connectv < 0){
        printf("Connection failed\n");
        return EXIT_FAILURE;
    }

    printf("Connection success! Je suis client. mon id est %d\n", getpid());

    while(running)
    {
        memset(buffer, '\0', sizeof(buffer));
        // printf("nombre aleatoire = %d\n", rand() % 100);
        int res = read(SocketFD, buffer, sizeof(buffer));
        if(res ==0){
            close(SocketFD);
            atexit(exit_message);
            exit(EXIT_FAILURE);
        }
        printf("Data reçu : %s\n", buffer);
        sleep(2);
    }
    close(SocketFD);

    printf("Apres la boucle...\n");
    atexit(exit_message);
    exit(EXIT_SUCCESS);
}
