#include <stdio.h> 
#include <unistd.h> //sleep()
#include<stdlib.h> //EXIT_SUCCESS

int main()
{
    printf("Avant la boucle\n");
    while(1)
    {
        printf("pid=%d\n", getpid());
        printf("ppid=%d\n", getppid());
        printf("nombre aleatoire = %d\n", rand() % 100);
        sleep(1);
    }
    printf("Apres la boucle\n");
    return EXIT_SUCCESS;
}