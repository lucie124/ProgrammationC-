#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool
#include <sys/types.h> // wait()
#include <sys/wait.h> // wait()
#include <string.h> //strlen()
#include <fcntl.h> //for open 
#include <limits.h>
#include <sys/stat.h>   //for mkfifo
#include <time.h>
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

    char str[10];

    // TCP variable
    int SocketFD = 0;
    int bindv = 0;
    int listenv = 0;
    int acceptFD = 0;
    struct sockaddr_in LocalAddr = {0};
    struct sockaddr_in RemoteAddr = {0}; //对方地址信息
	socklen_t socklen = 0;  

    // create socket
    SocketFD = socket(AF_INET, SOCK_STREAM, 0); 
	if(SocketFD < 0)
	{
		printf("Create socket failed\n");
		return 0;
	}	

    LocalAddr.sin_family = AF_INET;
	LocalAddr.sin_port = htons(PORT); 
	LocalAddr.sin_addr.s_addr=htonl(INADDR_ANY); 

    //bind
    bindv = bind(SocketFD, (void *)&LocalAddr, sizeof(LocalAddr));
    if(bindv < 0){
        printf("Bind failed\n");
		return EXIT_FAILURE;
    }

    //listen
    listenv = listen(SocketFD,5);
    if(listenv < 0)
	{
		printf("Listen failed\n");
		return EXIT_FAILURE;
	}

    //accept
    acceptFD = accept(SocketFD, (void *)&RemoteAddr, &socklen);
    if(acceptFD < 0)
	{
		printf("Accept failed\n");
		return EXIT_FAILURE;
    }

    printf("Accept success! Je suis server. mon id est %d\n", getpid());

    while(running)
    {
        srand(time(NULL));
        int a = rand()%100;
        sprintf(str,"%d",a);
        printf("Data envoyé : %s\n",str);
        char * msg = str;
        write(acceptFD, msg, strlen(msg));
        sleep(2);
    }
    close(acceptFD);
    close(SocketFD);

    printf("Apres la boucle...\n");
    atexit(exit_message);
    return EXIT_SUCCESS;
}

